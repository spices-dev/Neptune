/**
* @file PhysicalDevice.cpp.
* @brief The PhysicalDevice Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PhysicalDevice.h"
#include "Device.h"
#include "Instance.h"
#include "Surface.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"
#include "Device/Graphics/Backend/Vulkan/Extension/HDR.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IGetSurfaceCapabilities.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IGetPhysicalDeviceProperties.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {

	PhysicalDevice::PhysicalDevice(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	void PhysicalDevice::Create()
    {
		NEPTUNE_PROFILE_ZONE

        const auto instance = GetContext().Get<IInstance>()->Handle();

        uint32_t deviceCount = 0;
        VULKAN_CHECK(vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr))

        if (deviceCount == 0) 
		{
			NEPTUNE_LOG_CORE(E) << "Failed to find GPUs with Vulkan support.";
			return;
		}

        std::vector<VkPhysicalDevice> PhysicalDevices(deviceCount);
        VULKAN_CHECK(vkEnumeratePhysicalDevices(instance, &deviceCount, PhysicalDevices.data()))
		
		Container::LinkedUnorderedMap<VkPhysicalDevice, SP<Extensions>> satisfied;
		
		for (const auto& physicalDevice : PhysicalDevices)
		{
			if (auto extensions = DeviceDetection(physicalDevice))
			{
				satisfied.PushBack(physicalDevice, extensions);
			}
		}
		if (satisfied.Empty())
		{
			NEPTUNE_LOG_CORE(E) << "Failed to find GPU Physical Device that satisfied our needs.";
			return;
		}
		
		auto best = SelectBestDevice(satisfied.Keys());
		
		GetContext().Get<IExtensions>()->CopyFrom(satisfied.At(best));
		
		m_PhysicalDevice.SetHandle(best);
		
		PropertiesQuery();
    }

	SP<Extensions> PhysicalDevice::DeviceDetection(const VkPhysicalDevice& device) const
	{
		NEPTUNE_PROFILE_ZONE

		auto extensions = GetContext().Get<IExtensions>()->Copy();
		
		auto* surface = GetContext().Has<ISurface>() ? GetContext().Get<ISurface>()->Handle() : nullptr;

		if(!IsExtensionMeetDemand          (extensions.get(), device         )) return nullptr;
  
		if(!IsPropertyMeetDemand           (extensions.get(), device         )) return nullptr;
  
		if(!IsFeatureMeetDemand            (extensions.get(), device         )) return nullptr;
  
		if(!IsQueueMeetDemand              (extensions.get(), device, surface)) return nullptr;
		  
		if(!IsSurfaceCapabilityMeetDemand  (extensions.get(), device, surface)) return nullptr;
  
		if(!IsSurfaceFormatMeetDemand      (extensions.get(), device, surface)) return nullptr;
		
		return extensions;
	}
	
	VkPhysicalDevice PhysicalDevice::SelectBestDevice(const std::vector<VkPhysicalDevice>& devices) const
	{
		NEPTUNE_PROFILE_ZONE
		
		std::stringstream ss;
		
		ss << "Device List: ";
		
		for (size_t i = 0; i < devices.size(); ++i)
		{
			VkPhysicalDeviceProperties props;
			vkGetPhysicalDeviceProperties(devices[i], &props);
			
			ss <<"\n" << "Device [ " << i << " ]: " << "\n"
				<< "    Name:            " << props.deviceName << "\n"
				<< "    Type:            " << Vulkan::ToString(props.deviceType) << "\n"
				<< "    DeviceID:        " << props.deviceID << "\n"
				<< "    VendorID:        " << props.vendorID << "\n"
				<< "    DriverVersion:   " << props.driverVersion << "\n"
				<< "    API Version:     " << VK_VERSION_MAJOR(props.apiVersion) << "." << VK_VERSION_MINOR(props.apiVersion) << "." << VK_VERSION_PATCH(props.apiVersion);
		}
		
		ss << "\n" << "Device Selected first.";
		
		NEPTUNE_LOG_CORE(I) << ss.str();
		
		return devices.front();
	}
	
	void PhysicalDevice::PropertiesQuery()
	{
		NEPTUNE_PROFILE_ZONE
		
		VkPhysicalDeviceProperties2          deviceProperties{};
		deviceProperties.sType             = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		deviceProperties.pNext             = nullptr;

		Middleware::IGetPhysicalDeviceProperties::Create(GetContext())->GetProperties(m_PhysicalDevice.GetHandle(), deviceProperties);

		m_Properties                       = deviceProperties.properties;
	}
	
	bool PhysicalDevice::IsExtensionMeetDemand(Extensions* extensions, const VkPhysicalDevice& device) const
	{
		NEPTUNE_PROFILE_ZONE

		VkPhysicalDeviceProperties2          deviceProperties{};
		deviceProperties.sType             = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		deviceProperties.pNext             = nullptr;

		Middleware::IGetPhysicalDeviceProperties::Create(extensions)->GetProperties(device, deviceProperties);

		VkPhysicalDeviceProperties           properties{};
		properties                         = deviceProperties.properties;
		
		uint32_t extensionCount;
		VULKAN_CHECK(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr))

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		VULKAN_CHECK(vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data()))

		bool coreSatisfied = true;
		
		std::vector<EExtension> removedExtension;
		
		extensions->GetContext()->View([&](const auto e, const auto& extension) {
    		
			bool satisfy = true;
			const auto& exts = extension->GetDeviceExtensions();
    		
			auto filtered = std::views::keys(exts | std::views::filter([](const auto& pair) {
				return pair.second;
			}));
			
			std::ranges::for_each(filtered, [&](const auto& name) {

				if (std::ranges::all_of(availableExtensions, [&](const auto& ext) { return ext.extensionName != name; }))
				{
					if (extension->GetState() == Extension::EExtensionState::Core)
					{
						coreSatisfied = false;
						
						NEPTUNE_LOG_CORE(E) << "Device Extension Required: [ " << name << " ], Which is not satisfied with device: " << properties.deviceName;
					}
					else
					{
						NEPTUNE_LOG_CORE(W) << "Device Extension Required: [ " << name << " ], Which is not satisfied with device: " << properties.deviceName;
					}
    				
					satisfy = false;
				}
			});
    		
			if (!satisfy)
			{
				removedExtension.emplace_back(e);
			}
		});
    	
		std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			extensions->GetContext()->UnRegistry(e);
		});
    	
		return coreSatisfied;
	}

	bool PhysicalDevice::IsPropertyMeetDemand(Extensions* extensions, const VkPhysicalDevice& device) const
	{
		NEPTUNE_PROFILE_ZONE

		VkPhysicalDeviceProperties2          deviceProperties{};
		deviceProperties.sType             = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		deviceProperties.pNext             = nullptr;

		extensions->BuildPropertyChain(&deviceProperties.pNext);

		Middleware::IGetPhysicalDeviceProperties::Create(extensions)->GetProperties(device, deviceProperties);

		bool coreSatisfied = true;
		
		std::vector<EExtension> removedExtension;
		
		extensions->GetContext()->View([&](const auto e, const auto& extension) {
			
			if (!extension->IsPropertiesSatisfied())
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;
					
					NEPTUNE_LOG_CORE(E) << "Device Property Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Device Property Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
		std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			extensions->GetContext()->UnRegistry(e);
		});
		
		return coreSatisfied;
	}

	bool PhysicalDevice::IsFeatureMeetDemand(Extensions* extensions, const VkPhysicalDevice& device) const
	{
		NEPTUNE_PROFILE_ZONE

		VkPhysicalDeviceFeatures2                             deviceFeatures {};
		deviceFeatures.sType                                = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		deviceFeatures.pNext                                = nullptr;
		
		extensions->BuildFeatureChain(&deviceFeatures.pNext);

		vkGetPhysicalDeviceFeatures2(device, &deviceFeatures);

		bool coreSatisfied = true;
		
		std::vector<EExtension> removedExtension;
		
		extensions->GetContext()->View([&](const auto e, const auto& extension) {
			
			if (!extension->IsFeaturesSatisfied())
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;

					NEPTUNE_LOG_CORE(E) << "Device Feature Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Device Feature Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
		std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			extensions->GetContext()->UnRegistry(e);
		});
		
		return coreSatisfied;
	}

	bool PhysicalDevice::IsSurfaceCapabilityMeetDemand(Extensions* extensions, const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const
	{
		NEPTUNE_PROFILE_ZONE
		
		if (surface)
		{
			VkSurfaceCapabilities2KHR                             capabilities{};
			capabilities.sType                                  = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
			capabilities.pNext                                  = nullptr;

			VkPhysicalDeviceSurfaceInfo2KHR                       surfaceInfo{};
			surfaceInfo.sType                                   = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
			surfaceInfo.surface                                 = surface;
			surfaceInfo.pNext                                   = nullptr;
		
			extensions->BuildSurfaceCapabilityChain(&capabilities.pNext);
		
			Middleware::IGetSurfaceCapabilities::Create(extensions)->GetCapabilities(device, surfaceInfo, capabilities);
		}
		
		bool coreSatisfied = true;
		
		std::vector<EExtension> removedExtension;
		
		extensions->GetContext()->View([&](const auto e, const auto& extension) {
			
			if (!extension->IsSurfaceCapabilitiesSatisfied())
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;

					NEPTUNE_LOG_CORE(E) << "Device Surface Capabilities Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Device Surface Capabilities Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
		std::ranges::for_each(removedExtension, [&](const auto& e) {
    		
			extensions->GetContext()->UnRegistry(e);
		});
		
		return coreSatisfied;
	}
	
	bool PhysicalDevice::IsQueueMeetDemand(Extensions* extensions, const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const
	{
		NEPTUNE_PROFILE_ZONE

		auto queueChain = extensions->BuildQueueChain(device, surface);
		
		bool coreSatisfied = true;

		std::vector<EExtension> removedExtension;
		
		extensions->GetContext()->View([&](const auto e, const auto& extension) {
			
			if (!extension->IsQueueSatisfied(queueChain))
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;

					NEPTUNE_LOG_CORE(E) << "Device Queue Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Device Queue Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
		std::ranges::for_each(removedExtension, [&](const auto& e) {

			extensions->GetContext()->UnRegistry(e);
		});
		
		return coreSatisfied;
	}

	bool PhysicalDevice::IsSurfaceFormatMeetDemand(Extensions* extensions, const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const
	{
		NEPTUNE_PROFILE_ZONE
		
		std::vector<VkSurfaceFormatKHR> formats;
		
		if (surface)
		{
			uint32_t formatCount;

			VULKAN_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr))

			if (formatCount)
			{
				formats.resize(formatCount);
		
				VULKAN_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, formats.data()))
			}
		}
		
		bool coreSatisfied = true;

		std::vector<EExtension> removedExtension;
		
		extensions->GetContext()->View([&](const auto e, const auto& extension) {
			
			if (!extension->IsSurfaceFormatsSatisfied(formats))
			{
				if (extension->GetState() == Extension::EExtensionState::Core)
				{
					coreSatisfied = false;

					NEPTUNE_LOG_CORE(E) << "Device Surface Formats Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				else
				{
					NEPTUNE_LOG_CORE(W) << "Device Surface Formats Required: [ " << Vulkan::ToString(e) << " ], Which is not satisfied";
				}
				
				removedExtension.emplace_back(e);
			}
			
		});
		
		std::ranges::for_each(removedExtension, [&](const auto& e) {

			extensions->GetContext()->UnRegistry(e);
		});
		
		return coreSatisfied;
	}
	
	bool PhysicalDevice::IsOpticalFlowSessionSupport(VkFormat format, VkOpticalFlowUsageFlagsNV usage)
	{
		NEPTUNE_PROFILE_ZONE

		VkOpticalFlowImageFormatInfoNV         formatInfo{};
		formatInfo.sType                     = VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_INFO_NV;
		formatInfo.usage                     = usage;

		uint32_t count = 0;
		VULKAN_CHECK(vkGetPhysicalDeviceOpticalFlowImageFormatsNV(Handle(), &formatInfo, &count, nullptr))

		std::vector<VkOpticalFlowImageFormatPropertiesNV> formats(count, { VK_STRUCTURE_TYPE_OPTICAL_FLOW_IMAGE_FORMAT_PROPERTIES_NV });
		VULKAN_CHECK(vkGetPhysicalDeviceOpticalFlowImageFormatsNV(Handle(), &formatInfo, &count, formats.data()))

		if (!std::ranges::any_of(formats.begin(), formats.end(), [&](const auto& f) { return f.format == format; }))
		{
			NEPTUNE_LOG_CORE(E) << "Format Not Supported In OpticalFlowSession.";
			return false;
		}

		VkFormatProperties3                    properties3{};
		properties3.sType                    = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3;
		
		VkFormatProperties2                    properties2{}; 
		properties2.sType                    = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
		properties2.pNext                    = &properties3;

		vkGetPhysicalDeviceFormatProperties2(Handle(), format, &properties2);
		if (usage & VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV && !(properties3.optimalTilingFeatures & VK_FORMAT_FEATURE_2_OPTICAL_FLOW_IMAGE_BIT_NV))
		{
			NEPTUNE_LOG_CORE(E) << "VK_FORMAT_FEATURE_2_OPTICAL_FLOW_IMAGE_BIT_NV Not Supported OPTICAL_FLOW_IMAGE_BIT.";
			return false;
		}

		if (usage & VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV && !(properties3.optimalTilingFeatures & VK_FORMAT_FEATURE_2_OPTICAL_FLOW_VECTOR_BIT_NV))
		{
			NEPTUNE_LOG_CORE(E) << "VK_FORMAT_FEATURE_2_OPTICAL_FLOW_IMAGE_BIT_NV Not Supported OPTICAL_FLOW_VECTOR_BIT.";
			return false;
		}

		VkPhysicalDeviceImageFormatInfo2       formatInfo2{};
		formatInfo2.sType                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
		formatInfo2.format                   = format;
		formatInfo2.type                     = VK_IMAGE_TYPE_2D;
		formatInfo2.tiling                   = VK_IMAGE_TILING_OPTIMAL;
		formatInfo2.usage                    = VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
		formatInfo2.pNext                    = &formatInfo;

		VkImageFormatProperties2               formatProperties2{};
		formatProperties2.sType              = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;

		VULKAN_CHECK(vkGetPhysicalDeviceImageFormatProperties2(Handle(), &formatInfo2, &formatProperties2))

		return true;
	}

	VideoSessionProperty PhysicalDevice::QueryVideoSessionProperty(const VkVideoProfileInfoKHR& videoProfile)
	{
		NEPTUNE_PROFILE_ZONE

		static VkVideoEncodeAV1CapabilitiesKHR       encodeAV1Capabilities { VK_STRUCTURE_TYPE_VIDEO_ENCODE_AV1_CAPABILITIES_KHR };
		static VkVideoEncodeH264CapabilitiesKHR      encodeH264Capabilities{ VK_STRUCTURE_TYPE_VIDEO_ENCODE_H264_CAPABILITIES_KHR };
		static VkVideoEncodeH265CapabilitiesKHR      encodeH265Capabilities{ VK_STRUCTURE_TYPE_VIDEO_ENCODE_H265_CAPABILITIES_KHR };
		static VkVideoEncodeCapabilitiesKHR          encodeCapabilities    { VK_STRUCTURE_TYPE_VIDEO_ENCODE_CAPABILITIES_KHR };

		static VkVideoDecodeVP9CapabilitiesKHR       decodeVP9Capabilities { VK_STRUCTURE_TYPE_VIDEO_DECODE_VP9_CAPABILITIES_KHR };
		static VkVideoDecodeAV1CapabilitiesKHR       decodeAV1Capabilities { VK_STRUCTURE_TYPE_VIDEO_DECODE_AV1_CAPABILITIES_KHR };
		static VkVideoDecodeH264CapabilitiesKHR      decodeH264Capabilities{ VK_STRUCTURE_TYPE_VIDEO_DECODE_H264_CAPABILITIES_KHR };
		static VkVideoDecodeH265CapabilitiesKHR      decodeH265Capabilities{ VK_STRUCTURE_TYPE_VIDEO_DECODE_H265_CAPABILITIES_KHR };
		static VkVideoDecodeCapabilitiesKHR          decodeCapabilities    { VK_STRUCTURE_TYPE_VIDEO_DECODE_CAPABILITIES_KHR };

		VideoSessionProperty                       property{};

		VkVideoCapabilitiesKHR&                    capabilities = property.capabilities;
		capabilities.sType                      = VK_STRUCTURE_TYPE_VIDEO_CAPABILITIES_KHR;

		switch (videoProfile.videoCodecOperation)
		{
			case VK_VIDEO_CODEC_OPERATION_ENCODE_H264_BIT_KHR:
			{
				encodeCapabilities.pNext        = &encodeH264Capabilities;
				capabilities.pNext              = &encodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_ENCODE_H265_BIT_KHR:
			{
				encodeCapabilities.pNext        = &encodeH265Capabilities;
				capabilities.pNext              = &encodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_ENCODE_AV1_BIT_KHR:
			{
				encodeCapabilities.pNext        = &encodeAV1Capabilities;
				capabilities.pNext              = &encodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_VP9_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeVP9Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_H264_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeH264Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_H265_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeH265Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
			case VK_VIDEO_CODEC_OPERATION_DECODE_AV1_BIT_KHR:
			{
				decodeCapabilities.pNext        = &decodeAV1Capabilities;
				capabilities.pNext              = &decodeCapabilities;
				break;
			}
		}

		VULKAN_CHECK(vkGetPhysicalDeviceVideoCapabilitiesKHR(Handle(), &videoProfile, &capabilities))

		if (decodeCapabilities.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_COINCIDE_BIT_KHR)
		{
			 // NV, Intel
			auto dpbFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR | VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR, { videoProfile });

            property.dpbFormat = dpbFormats[0];
            property.dstFormat = dpbFormats[0];
		}
		else if (decodeCapabilities.flags & VK_VIDEO_DECODE_CAPABILITY_DPB_AND_OUTPUT_DISTINCT_BIT_KHR)
		{
			// AMD
			auto dpbFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DPB_BIT_KHR, { videoProfile });
            auto outFormats = GetVideoFormats(VK_IMAGE_USAGE_VIDEO_DECODE_DST_BIT_KHR, { videoProfile });
           
            property.dpbFormat = dpbFormats[0];
            property.dstFormat = outFormats[0];
		}
		else
		{
			NEPTUNE_LOG_CORE(E) << "Unsupported Decode Capability Flags.";
        }

		// Use One DPB as dst image.
		assert(property.dpbFormat == property.dstFormat);

		return property;
	}

	bool PhysicalDevice::IsOpticalFlowSessionSupport(VkFormat inputFormat, VkFormat outFormat)
	{
		NEPTUNE_PROFILE_ZONE

		bool result = true;

		result &= IsOpticalFlowSessionSupport(inputFormat, VK_OPTICAL_FLOW_USAGE_INPUT_BIT_NV);
		result &= IsOpticalFlowSessionSupport(outFormat, VK_OPTICAL_FLOW_USAGE_OUTPUT_BIT_NV);

		return result;
	}

	const SwapChainProperty& PhysicalDevice::QuerySwapChainProperty()
	{
		NEPTUNE_PROFILE_ZONE

		auto surface = GetContext().Get<ISurface>()->Handle();
    
		VkSurfaceCapabilities2KHR               capabilities{};
		capabilities.sType                    = VK_STRUCTURE_TYPE_SURFACE_CAPABILITIES_2_KHR;
		capabilities.pNext                    = nullptr;

		VkPhysicalDeviceSurfaceInfo2KHR         surfaceInfo{};
		surfaceInfo.sType                     = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SURFACE_INFO_2_KHR;
		surfaceInfo.surface                   = GetContext().Get<ISurface>()->Handle();
		surfaceInfo.pNext                     = nullptr;
		
		Middleware::IGetSurfaceCapabilities::Create(GetContext())->GetCapabilities(Handle(), surfaceInfo, capabilities);

		SwapChainProperty                       property{};
		property.capabilities                 = capabilities.surfaceCapabilities;

		if (property.capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			property.surfaceSize = property.capabilities.currentExtent;
		}
		else
		{
			NEPTUNE_LOG_CORE(E) << "Surface Extent is infinity.";
		}

		uint32_t formatCount;

		VULKAN_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(Handle(), surface, &formatCount, nullptr))

		if (formatCount != 0)
		{
			property.formats.resize(formatCount);

			VULKAN_CHECK(vkGetPhysicalDeviceSurfaceFormatsKHR(Handle(), surface, &formatCount, property.formats.data()))

			property.format = property.formats[0];

			for (const auto& availableFormat : property.formats)
			{
				if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM &&
					availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				{
					property.format = availableFormat;

					break;
				}
			}
		}

		if (auto p = GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IHDR>())
		{
			property.format = p->GetFormat(Graphic::EHDRSurface::ExSRGB);
		}
		
		uint32_t presentModeCount;

		VULKAN_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(Handle(), surface, &presentModeCount, nullptr))

		if (presentModeCount != 0)
		{
			property.presentModes.resize(presentModeCount);

			VULKAN_CHECK(vkGetPhysicalDeviceSurfacePresentModesKHR(Handle(), surface, &presentModeCount, property.presentModes.data()))

			property.presentMode = property.presentModes[0];

			for (const auto& availablePresentMode : property.presentModes)
			{
				if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				{
					property.presentMode = availablePresentMode;
					break;
				}
			}
		}

		m_SwapChainProperty = property;

		return m_SwapChainProperty;
	}

	std::vector<const char*> PhysicalDevice::GetExtensionRequirements() const
	{
		NEPTUNE_PROFILE_ZONE

		std::vector<const char*> extensions;
		
		GetContext().Get<IExtensions>()->GetContext()->View([&](const auto e, const auto& extension) {
				
			const auto& exts = extension->GetDeviceExtensions();
  				
			auto filtered = std::views::keys(exts | std::views::filter([](const auto& pair) {
				return pair.second;
			}));
			
			std::ranges::for_each(filtered, [&](const auto& name) { extensions.emplace_back(name.c_str()); });
		});
		
		return extensions;
	}

	std::vector<VkFormat> PhysicalDevice::GetVideoFormats(VkImageUsageFlags imageUsage, const std::vector<VkVideoProfileInfoKHR>& videoProfile)
	{
		NEPTUNE_PROFILE_ZONE

		VkVideoProfileListInfoKHR                videoProfiles{};
		videoProfiles.sType                    = VK_STRUCTURE_TYPE_VIDEO_PROFILE_LIST_INFO_KHR;
		videoProfiles.profileCount             = videoProfile.size();
		videoProfiles.pProfiles                = videoProfile.data();
		videoProfiles.pNext                    = nullptr;
		
		VkPhysicalDeviceVideoFormatInfoKHR       videoFormatInfo {};
		videoFormatInfo.sType                  = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VIDEO_FORMAT_INFO_KHR;
		videoFormatInfo.imageUsage             = imageUsage;
		videoFormatInfo.pNext                  = &videoProfiles;

		uint32_t supportedFormatCount = 0;
        VULKAN_CHECK(vkGetPhysicalDeviceVideoFormatPropertiesKHR(Handle(), &videoFormatInfo, &supportedFormatCount, nullptr))

		std::vector<VkVideoFormatPropertiesKHR> supportedFormats(supportedFormatCount, { VK_STRUCTURE_TYPE_VIDEO_FORMAT_PROPERTIES_KHR });
		VULKAN_CHECK(vkGetPhysicalDeviceVideoFormatPropertiesKHR(Handle(), &videoFormatInfo, &supportedFormatCount, supportedFormats.data()))

		std::vector<VkFormat> formats;
		std::ranges::for_each(supportedFormats, [&](const auto& format){
			formats.emplace_back(format.format);
		});

		return formats;
	}
}

#endif