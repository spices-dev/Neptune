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
#include "Device/Graphics/Backend/Vulkan/Extension/PresentTiming.h"
#include "Device/Graphics/Backend/Vulkan/Extension/SwapChainMaintenance1.h"
#include "Device/Graphics/Backend/Vulkan/Extension/FrameBoundary.h"

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

			if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IPresentTiming>())
			{
				createInfo.flags                  |= VK_SWAPCHAIN_CREATE_PRESENT_TIMING_BIT_EXT;
				createInfo.flags                  |= VK_SWAPCHAIN_CREATE_PRESENT_ID_2_BIT_KHR;
			}
			
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

    	if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IPresentTiming>())
    	{
    		uint32_t queueSize = count * 2u;
    		
    		VULKAN_CHECK(vkSetSwapchainPresentTimingQueueSizeEXT(GetContext().Get<IDevice>()->Handle(), Handle(), queueSize))
    		
			m_PresentTimingState.timings.assign(queueSize, {});
    		m_PresentTimingState.stageTimes.assign(static_cast<size_t>(queueSize) * PresentTimingState::kMaxStages, {});
    		
    		for (uint32_t i = 0; i < queueSize; ++i)
    		{
    			m_PresentTimingState.timings[i].sType             = VK_STRUCTURE_TYPE_PAST_PRESENTATION_TIMING_EXT;
    			m_PresentTimingState.timings[i].pPresentStages    = &m_PresentTimingState.stageTimes[static_cast<size_t>(i) * PresentTimingState::kMaxStages];
    			m_PresentTimingState.timings[i].presentStageCount = PresentTimingState::kMaxStages;
    		}
    		
    		QueryTimingProperties();
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
    	
    	VkFenceCreateInfo                       fenceInfo{};
    	fenceInfo.sType                       = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    	fenceInfo.flags                       = VK_FENCE_CREATE_SIGNALED_BIT;
    	
    	if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::ISwapChainMaintenance1>())
    	{
    		for (size_t i = 0; i < m_SwapChainImage.size(); ++i)
    		{
    			auto fence = CreateUP<Resource::SwapChainFence>(GetContext());

    			fence->CreateSwapChainFence(fenceInfo);
 
    			fence->ResetFence();
    			
    			m_SwapChainImageFence.emplace_back(std::move(fence));
    		}
    	}
    }

	void SwapChain::PollPresentTiming()
	{
    	NEPTUNE_PROFILE_ZONE
    	
    	VkPastPresentationTimingInfoEXT            info{};
    	info.sType                               = VK_STRUCTURE_TYPE_PAST_PRESENTATION_TIMING_INFO_EXT;
    	info.swapchain                           = Handle();
    	
    	VkPastPresentationTimingPropertiesEXT      out{};
    	out.sType                                = VK_STRUCTURE_TYPE_PAST_PRESENTATION_TIMING_PROPERTIES_EXT;
    	out.presentationTimingCount              = (uint32_t)m_PresentTimingState.timings.size();
    	out.pPresentationTimings                 = m_PresentTimingState.timings.data();

    	auto result = vkGetPastPresentationTimingEXT(GetContext().Get<IDevice>()->Handle(), &info, &out);
    	if (result != VK_SUCCESS && result != VK_INCOMPLETE)
    	{
    		VULKAN_CHECK(result)
    		
    		return;
    	}

    	if (out.timeDomainsCounter != m_PresentTimingState.domainsCounter)
    	{
    		QueryTimeDomains();
    	}
    	if (out.timingPropertiesCounter != m_PresentTimingState.tpCount)
    	{
    		QueryTimingProperties();
    	}

    	uint32_t completed = 0;
    	for (uint32_t i = 0; i < out.presentationTimingCount; ++i)
    	{
    		const auto& t = m_PresentTimingState.timings[i];
    		if (!t.reportComplete) continue;

    		++completed;
    		
    		if (t.timeDomainId != m_PresentTimingState.timeDomainId) continue;
    		if (t.presentId == 0 || t.presentId <= m_PresentTimingState.lastPresentId) continue;

    		for (uint32_t k = 0; k < t.presentStageCount; ++k)
    		{
    			if (t.pPresentStages[k].stage == m_PresentTimingState.stage && t.pPresentStages[k].time != 0)
    			{
    				m_PresentTimingState.lastPresentId   = t.presentId;
    				m_PresentTimingState.lastPresentTime = t.pPresentStages[k].time;
    				break;
    			}
    		}
    	}
    	
    	m_PresentTimingState.pending -= std::min(m_PresentTimingState.pending, completed);
	}
	
	bool SwapChain::QueryTimeDomains()
	{
		NEPTUNE_PROFILE_ZONE

		VkSwapchainTimeDomainPropertiesEXT         td{};
		td.sType                                 = VK_STRUCTURE_TYPE_SWAPCHAIN_TIME_DOMAIN_PROPERTIES_EXT;

		VULKAN_CHECK(vkGetSwapchainTimeDomainPropertiesEXT(GetContext().Get<IDevice>()->Handle(), Handle(), &td, nullptr))

		std::vector<VkTimeDomainKHR>               domains(td.timeDomainCount);
		std::vector<uint64_t>                      ids(td.timeDomainCount);
		td.pTimeDomains                          = domains.data();
		td.pTimeDomainIds                        = ids.data();

		uint64_t counter = 0;
		auto result = vkGetSwapchainTimeDomainPropertiesEXT(GetContext().Get<IDevice>()->Handle(), Handle(), &td, &counter);
		if (result != VK_SUCCESS && result != VK_INCOMPLETE)
		{
			VULKAN_CHECK(result)
			
			return false;
		}

		for (uint32_t i = 0; i < td.timeDomainCount; ++i)
		{
			if (domains[i] == VK_TIME_DOMAIN_SWAPCHAIN_LOCAL_EXT)
			{
				m_PresentTimingState.timeDomainId = ids[i];
				m_PresentTimingState.targetStage  = 0;
			}
			else if (domains[i] == VK_TIME_DOMAIN_PRESENT_STAGE_LOCAL_EXT)
			{
				m_PresentTimingState.timeDomainId = ids[i];
				m_PresentTimingState.targetStage  = m_PresentTimingState.stage;
			}
		}

		m_PresentTimingState.domainsCounter  = counter;
		m_PresentTimingState.lastPresentId   = 0;
		m_PresentTimingState.lastPresentTime = 0;

		return true;
	}

	void SwapChain::QueryTimingProperties()
    {
    	NEPTUNE_PROFILE_ZONE
    	
    	VkSwapchainTimingPropertiesEXT             p{};
    	p.sType                                  = VK_STRUCTURE_TYPE_SWAPCHAIN_TIMING_PROPERTIES_EXT;

    	uint64_t counter = 0;
    	VULKAN_CHECK(vkGetSwapchainTimingPropertiesEXT(GetContext().Get<IDevice>()->Handle(), Handle(), &p, &counter))

    	m_PresentTimingState.tpCount             = counter;
    	m_PresentTimingState.tp                  = p;
    }
	
	uint64_t SwapChain::ComputeTargetTime(uint64_t presentId) const
    {
    	if (!m_TargetFrameInterval || m_PresentTimingState.lastPresentTime == 0) return 0;

    	uint64_t ipd = m_TargetFrameInterval;
    	
    	if (m_PresentTimingState.tp.refreshInterval != 0 && m_PresentTimingState.tp.refreshInterval != UINT64_MAX)
    	{
    		const uint64_t n = std::max<uint64_t>(1, (ipd + m_PresentTimingState.tp.refreshInterval / 2) / m_PresentTimingState.tp.refreshInterval);
    		
    		ipd = n * m_PresentTimingState.tp.refreshInterval;
    	}

    	return m_PresentTimingState.lastPresentTime + (presentId - m_PresentTimingState.lastPresentId) * ipd;
    }
	
	bool SwapChain::GetNextImage(VkSemaphore semaphore, uint32_t& imageIndex) const
	{
		NEPTUNE_PROFILE_ZONE

		const auto result = m_SwapChain->GetNextImage(semaphore, imageIndex);

    	if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::ISwapChainMaintenance1>())
    	{
    		m_SwapChainImageFence[imageIndex]->WaitReset();
    	}
    	
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

	bool SwapChain::Present(VkPresentInfoKHR& info, uint64_t frameId)
	{
		NEPTUNE_PROFILE_ZONE

    	info.pSwapchains                         = &Handle();

    	VkFrameBoundaryEXT                         boundary{};
    	if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IFrameBoundary>())
		{
    		boundary.sType                       = VK_STRUCTURE_TYPE_FRAME_BOUNDARY_EXT;
			boundary.flags                       = VK_FRAME_BOUNDARY_FRAME_END_BIT_EXT;
			boundary.frameID                     = frameId;
			boundary.imageCount                  = 1;
			boundary.pImages                     = &m_SwapChainImage[*info.pImageIndices]->Handle();
    		boundary.pNext                       = info.pNext;
    		
    		info.pNext                           = &boundary;
		}
    	
    	VkSwapchainPresentFenceInfoKHR            fenceInfo{};
    	if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::ISwapChainMaintenance1>())
    	{
    		fenceInfo.sType                      = VK_STRUCTURE_TYPE_SWAPCHAIN_PRESENT_FENCE_INFO_KHR;
    		fenceInfo.swapchainCount             = info.swapchainCount;
    		fenceInfo.pFences                    = &m_SwapChainImageFence[*info.pImageIndices]->Handle();
    		fenceInfo.pNext                      = info.pNext;
    		
    		info.pNext                           = &fenceInfo;
    	}
    	
    	VkPresentId2KHR                            id{};
    	VkPresentTimingInfoEXT                     time{};
    	VkPresentTimingsInfoEXT                    times{};
    	if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IPresentTiming>())
    	{
    		QueryTimeDomains();
    		
    		id.sType                             = VK_STRUCTURE_TYPE_PRESENT_ID_2_KHR;
    		id.swapchainCount                    = 1;
    		id.pPresentIds                       = &frameId;
    		id.pNext                             = info.pNext;
    		
    		time.sType                           = VK_STRUCTURE_TYPE_PRESENT_TIMING_INFO_EXT;
    		time.flags                           = VK_PRESENT_TIMING_INFO_PRESENT_AT_NEAREST_REFRESH_CYCLE_BIT_EXT;
    		time.targetTime                      = ComputeTargetTime(frameId);
    		time.timeDomainId                    = m_PresentTimingState.timeDomainId;
    		time.presentStageQueries             = m_PresentTimingState.pending < m_PresentTimingState.queueSize ? m_PresentTimingState.stage : 0;
    		time.targetTimeDomainPresentStage    = m_PresentTimingState.targetStage;
    		
    		times.sType                          = VK_STRUCTURE_TYPE_PRESENT_TIMINGS_INFO_EXT;
    		times.swapchainCount                 = 1;
    		times.pTimingInfos                   = &time;
    		times.pNext                          = &id;
    		 
    		info.pNext                           = &times;
    	}
    	
		const auto result = vkQueuePresentKHR(GetContext().Get<IPresentQueue>()->Handle(), &info);

    	if (result == VK_ERROR_PRESENT_TIMING_QUEUE_FULL_EXT)
    	{
    		return true;
    	}
    	
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
		{
			return false;
		}
        
        VULKAN_CHECK(result)

        if (GetContext().Get<IExtensions>()->GetContext()->Get<Extension::IPresentTiming>())
        {
            if (m_PresentTimingState.pending < m_PresentTimingState.queueSize)
            {
                ++m_PresentTimingState.pending;
            }
            
            PollPresentTiming();
        }
        
		return true;
	}
}

#endif
