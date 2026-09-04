/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Device.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "ThreadQueue.h"
#include "DebugUtilsObject.h"
#include "Surface.h"
#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Queue.h"

namespace Neptune::Vulkan {

    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create();
    }

	void Device::Wait() const
	{
		NEPTUNE_PROFILE_ZONE

		m_Device.Wait();
	}

	void Device::Create()
    {
		NEPTUNE_PROFILE_ZONE

    	std::vector<UP<std::vector<float>>> queuePriorities;
    	std::unordered_map<uint32_t, VkDeviceQueueCreateInfo> queueInfoMap;

		auto queue = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>();

		for (const auto& family : queue->GetQueueFamilies() | std::views::values)
		{
			auto count = std::min(family.second, NThreadQueue + 1);
			
			auto priority = CreateUP<std::vector<float>>(count, 1.0f);

			if (queueInfoMap.contains(family.first))
			{
				if (queueInfoMap.at(family.first).queueCount >= count)
				{
					continue;
				}
			}

			VkDeviceQueueCreateInfo                    info{};
			info.sType                               = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			info.queueFamilyIndex                    = family.first;
			info.queueCount                          = count;
			info.pQueuePriorities                    = priority->data();

			queuePriorities.emplace_back(std::move(priority));
			queueInfoMap[family.first] = info;
		}

    	if (queue->HasPresentQueueFamily())
    	{
    		if (!std::ranges::any_of(queue->GetQueueFamilies(), [&](const auto& family) {
    			return family.second.first == queue->GetPresentQueueFamily();
    		}))
    		{
    			auto priority = CreateUP<std::vector<float>>(1, 1.0f);
    			
    			VkDeviceQueueCreateInfo                    info{};
    			info.sType                               = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    			info.queueFamilyIndex                    = queue->GetPresentQueueFamily();
    			info.queueCount                          = 1;
    			info.pQueuePriorities                    = priority->data();

    			queuePriorities.emplace_back(std::move(priority));
    			queueInfoMap[queue->GetPresentQueueFamily()] = info;
    		}
    	}
    	
    	std::vector<VkDeviceQueueCreateInfo> filtered;
    	filtered.reserve(queueInfoMap.size());
    	std::ranges::copy(std::views::values(queueInfoMap), std::back_inserter(filtered));
    	
    	const auto physicalDevice  = GetContext().Get<IPhysicalDevice>();
    	
		VkPhysicalDeviceFeatures2                                 deviceFeatures{};
		deviceFeatures.sType                                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		deviceFeatures.pNext                                    = nullptr;

    	GetContext().Get<IExtensions>()->BuildFeatureChainWithoutRepeat(&deviceFeatures.pNext);

    	vkGetPhysicalDeviceFeatures2(physicalDevice->Handle(), &deviceFeatures);

        VkDeviceCreateInfo                                        createInfo{};
		createInfo.sType                                        = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos                            = filtered.data();
		createInfo.queueCreateInfoCount                         = filtered.size();
		createInfo.pEnabledFeatures                             = VK_NULL_HANDLE;
		createInfo.enabledExtensionCount                        = physicalDevice->GetExtensionRequirements().size();
		createInfo.ppEnabledExtensionNames                      = physicalDevice->GetExtensionRequirements().data();
		createInfo.enabledLayerCount                            = 0;
		createInfo.pNext                                        = &deviceFeatures;

		m_Device.CreateDevice(physicalDevice->Handle(), &createInfo);
		DEBUGUTILS_SETOBJECTNAME(m_Device, physicalDevice->GetProperties().deviceName)

    	for (const auto&[bit, family] : queue->GetQueueFamilies())
    	{
    		switch (bit)
    		{
    			case VK_QUEUE_GRAPHICS_BIT:
    			{
    				GetContext().Registry<IGraphicQueue>(m_Device.GetDeviceQueue(family.first, 0));
    				GetContext().Registry<IGraphicThreadQueue>();

    				auto count = std::min(family.second, NThreadQueue + 1);

    				if (count == 1)
    				{
    					GetContext().Get<IGraphicThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, 0));
    					break;
    				}
    				
    				for (int i = 1; i < count; ++i)
    				{
						GetContext().Get<IGraphicThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, i));
					}
    				break;
    			}
    			case VK_QUEUE_COMPUTE_BIT:
    			{
					GetContext().Registry<IComputeQueue>(m_Device.GetDeviceQueue(family.first, 0));
					GetContext().Registry<IComputeThreadQueue>();

					auto count = std::min(family.second, NThreadQueue + 1);

    				if (count == 1)
    				{
    					GetContext().Get<IGraphicThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, 0));
    					break;
    				}
    				
					for (int i = 1; i < count; ++i)
					{
						GetContext().Get<IComputeThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, i));
					}
					break;
				}
    			case VK_QUEUE_TRANSFER_BIT:
    			{
					GetContext().Registry<ITransferThreadQueue>();
    				GetContext().Get<ITransferThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, 0));
    				
					break;
				}
    			case VK_QUEUE_VIDEO_DECODE_BIT_KHR:
    			{
					GetContext().Registry<IVideoDecodeThreadQueue>();
					GetContext().Get<IVideoDecodeThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, 0));
    				
					break;
				}
    			case VK_QUEUE_VIDEO_ENCODE_BIT_KHR:
    			{
					GetContext().Registry<IVideoEncodeThreadQueue>();
					GetContext().Get<IVideoEncodeThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, 0));
    				
					break;
				}
    			case VK_QUEUE_OPTICAL_FLOW_BIT_NV:
    			{
					GetContext().Registry<IOpticalFlowThreadQueue>();
					GetContext().Get<IOpticalFlowThreadQueue>()->Add(m_Device.GetDeviceQueue(family.first, 0));
    				
					break;
				}
    			default: break;
    		}
    	}

    	if (queue->HasPresentQueueFamily())
    	{
    		GetContext().Registry<IPresentQueue>(m_Device.GetDeviceQueue(queue->GetPresentQueueFamily(), 0));
    	}
    }

}

#endif