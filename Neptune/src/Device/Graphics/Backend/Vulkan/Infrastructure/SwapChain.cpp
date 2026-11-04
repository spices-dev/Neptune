/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "SwapChain.h"
#include "Device.h"
#include "Surface.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "DebugUtilsObject.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/HDR.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"

namespace Neptune::Vulkan {

    SwapChain::SwapChain(Context& context, EInfrastructure e, uint32_t count, Unit::SwapChain::Handle handle)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create(count, handle);
    }

	void SwapChain::Create(uint32_t count, Unit::SwapChain::Handle handle)
    {
		NEPTUNE_PROFILE_ZONE

		auto physicalDevice = GetContext().Get<IPhysicalDevice>();

		auto& property = physicalDevice->QuerySwapChainProperty();

    	count = std::clamp(count, property.capabilities.minImageCount, property.capabilities.maxImageCount);

    	{
			VkSwapchainCreateInfoKHR                 createInfo{};
			createInfo.sType                       = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
			createInfo.surface                     = GetContext().Get<ISurface>()->Handle();
			createInfo.minImageCount               = count;
			createInfo.imageFormat                 = property.format.format;
			createInfo.imageColorSpace             = property.format.colorSpace;
			createInfo.imageExtent                 = property.surfaceSize;
			createInfo.imageArrayLayers            = 1;
			createInfo.imageUsage                  = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | 
													 VK_IMAGE_USAGE_TRANSFER_DST_BIT;     // @brief StreamLine Required

			uint32_t queueFamilyIndices[2] = 
			{ 
				GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT),
				GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IQueue>()->GetPresentQueueFamily()
			};

			if (queueFamilyIndices[0] != queueFamilyIndices[1])
			{
				createInfo.imageSharingMode        = VK_SHARING_MODE_CONCURRENT;
				createInfo.queueFamilyIndexCount   = 2;
				createInfo.pQueueFamilyIndices     = queueFamilyIndices;
			}
			else 
			{
				createInfo.imageSharingMode        = VK_SHARING_MODE_EXCLUSIVE;
				createInfo.queueFamilyIndexCount   = 0;
				createInfo.pQueueFamilyIndices     = nullptr;
			}

			createInfo.preTransform                = property.capabilities.currentTransform;
			createInfo.compositeAlpha              = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
			createInfo.presentMode                 = property.presentMode;
			createInfo.clipped                     = VK_TRUE;
			createInfo.oldSwapchain                = handle;

			m_SwapChain = CreateUP<Unit::SwapChain>();

			m_SwapChain->CreateSwapchain(GetContext().Get<IDevice>()->Handle(), createInfo);

			DEBUGUTILS_SETOBJECTNAME(*m_SwapChain, ToString())
		}
    	
		if (GetContext().Get<IExtensions>()->GetContext()->Has<Extension::IHDR>())
		{
			VkHdrMetadataEXT                    meta {};
			meta.sType                        = VK_STRUCTURE_TYPE_HDR_METADATA_EXT;
			meta.displayPrimaryRed            = { 0.708f, 0.292f };
			meta.displayPrimaryGreen          = { 0.170f, 0.797f };
			meta.displayPrimaryBlue           = { 0.131f, 0.046f };
			meta.whitePoint                   = { 0.3127f, 0.3290f };
			meta.maxLuminance                 = 1000.0f;
			meta.minLuminance                 = 0.001f;
			meta.maxContentLightLevel         = 1000.0f;
			meta.maxFrameAverageLightLevel    = 100.0f;
			
			m_SwapChain->SetHdrMetadata(meta);
		}

		auto images = m_SwapChain->GetSwapchainImages();

		std::ranges::for_each(images, [&](const auto& image){
			
			auto swapChainImage = CreateUP<Resource::Image>(GetContext());

			swapChainImage->SetImage(image);
			
			{
				VkImageViewCreateInfo                   info{};
				info.sType                            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
				info.flags                            = 0;
				info.image                            = image;

				info.viewType                         = VK_IMAGE_VIEW_TYPE_2D;
				info.format                           = property.format.format;

				info.components.r                     = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.g                     = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.b                     = VK_COMPONENT_SWIZZLE_IDENTITY;
				info.components.a                     = VK_COMPONENT_SWIZZLE_IDENTITY;
													  
				info.subresourceRange.aspectMask      = VK_IMAGE_ASPECT_COLOR_BIT;
				info.subresourceRange.baseMipLevel    = 0;
				info.subresourceRange.levelCount      = 1;
				info.subresourceRange.baseArrayLayer  = 0;
				info.subresourceRange.layerCount      = 1;

				swapChainImage->CreateImageView(info);
			}

			{
				const auto& properties = GetContext().Get<IPhysicalDevice>()->GetProperties();
				
				VkSamplerCreateInfo                     samplerInfo{};
				samplerInfo.sType                     = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
				samplerInfo.magFilter                 = VK_FILTER_LINEAR;
				samplerInfo.minFilter                 = VK_FILTER_LINEAR;
				samplerInfo.addressModeU              = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeV              = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.addressModeW              = VK_SAMPLER_ADDRESS_MODE_REPEAT;
				samplerInfo.anisotropyEnable          = VK_TRUE;
				samplerInfo.maxAnisotropy             = properties.limits.maxSamplerAnisotropy;
				samplerInfo.borderColor               = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
				samplerInfo.unnormalizedCoordinates   = VK_FALSE;
				samplerInfo.compareEnable             = VK_FALSE;
				samplerInfo.compareOp                 = VK_COMPARE_OP_ALWAYS;
													  
				samplerInfo.mipmapMode                = VK_SAMPLER_MIPMAP_MODE_LINEAR;
				samplerInfo.mipLodBias                = 0.0f;
				samplerInfo.minLod                    = 0.0f;
				samplerInfo.maxLod                    = VK_LOD_CLAMP_NONE;

				swapChainImage->CreateSampler(samplerInfo);
			}

			swapChainImage->SetName("SwapChain");

			m_SwapChainImage.emplace_back(std::move(swapChainImage));
		});
    }

	bool SwapChain::GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		const auto result = m_SwapChain->GetNextImage(semaphore, imageIndex);

		if (result == VK_SUCCESS)
		{
			return true;
		}
		else if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			NEPTUNE_LOG_CORE(W) << "Failed to Acquire SwapChain Image: Out of Data.";
			
			return false;
		}
		else if (result == VK_SUBOPTIMAL_KHR)
		{
			NEPTUNE_LOG_CORE(W) << "Failed to Acquire SwapChain Image: SubOptimal.";
    		
    		return true;
		}

    	VULKAN_CHECK(result)

		return false;
	}

	bool SwapChain::Present(VkPresentInfoKHR& info) const
	{
		NEPTUNE_PROFILE_ZONE

		info.pSwapchains = &Handle();

		const auto result = vkQueuePresentKHR(GetContext().Get<IPresentQueue>()->Handle(), &info);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		{
			return false;
		}
        
        VULKAN_CHECK(result)

		return true;
	}
}

#endif
