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

		const auto& graphicFamily     = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_GRAPHICS_BIT);
		const auto& presentFamily     = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetPresentQueueFamil();
		const auto& computeFamily     = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_COMPUTE_BIT);
		const auto& transferFamily    = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_TRANSFER_BIT);
		const auto& videoEncodeFamily = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_VIDEO_ENCODE_BIT_KHR);
		const auto& videoDecodeFamily = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_VIDEO_DECODE_BIT_KHR);
		const auto& opticalFlowFamily = GetContext().Get<IExtensions>()->GetContext().Get<Extension::IQueue>()->GetQueueFamily(VK_QUEUE_OPTICAL_FLOW_BIT_NV);

		std::unordered_map<uint32_t, std::unordered_map<uint32_t, std::vector<VkQueue>>> queueFamilies;

		queueFamilies[graphicFamily][0]     = std::vector<VkQueue>(1 + NThreadQueue, VK_NULL_HANDLE);
		queueFamilies[presentFamily][1]     = std::vector<VkQueue>(1,                VK_NULL_HANDLE);
		queueFamilies[computeFamily][2]     = std::vector<VkQueue>(1 + NThreadQueue, VK_NULL_HANDLE);
		queueFamilies[transferFamily][3]    = std::vector<VkQueue>(1,                VK_NULL_HANDLE);
		queueFamilies[videoEncodeFamily][4] = std::vector<VkQueue>(1,                VK_NULL_HANDLE);
		queueFamilies[videoDecodeFamily][5] = std::vector<VkQueue>(1,                VK_NULL_HANDLE);
		queueFamilies[opticalFlowFamily][6] = std::vector<VkQueue>(1,                VK_NULL_HANDLE);

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::vector<SP<std::vector<float>>> QueuePriorities;
		for (auto& [family, idItems] : queueFamilies)
		{
			uint32_t count = 0;

			for (auto& queues : idItems | std::views::values)
			{
				count += queues.size();
			}

			auto queuePriority = CreateSP<std::vector<float>>(count, 1.0f);

			VkDeviceQueueCreateInfo                               queueCreateInfo{};
			queueCreateInfo.sType                               = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex                    = family;
			queueCreateInfo.queueCount                          = count;
			queueCreateInfo.pQueuePriorities                    = queuePriority->data();

			QueuePriorities.push_back(queuePriority);
			queueCreateInfos.push_back(queueCreateInfo);
		}
    	
    	const auto physicalDevice  = GetContext().Get<IPhysicalDevice>();
    	
		VkPhysicalDeviceFeatures2                                 deviceFeatures{};
		deviceFeatures.sType                                    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		deviceFeatures.pNext                                    = nullptr;

    	GetContext().Get<IExtensions>()->BuildFeatureChainWithoutRepeat(&deviceFeatures.pNext);

    	vkGetPhysicalDeviceFeatures2(physicalDevice->Handle(), &deviceFeatures);

        VkDeviceCreateInfo                                        createInfo{};
		createInfo.sType                                        = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos                            = queueCreateInfos.data();
		createInfo.queueCreateInfoCount                         = queueCreateInfos.size();
		createInfo.pEnabledFeatures                             = VK_NULL_HANDLE;
		createInfo.enabledExtensionCount                        = physicalDevice->GetExtensionRequirements().size();
		createInfo.ppEnabledExtensionNames                      = physicalDevice->GetExtensionRequirements().data();
		createInfo.enabledLayerCount                            = 0;
		createInfo.pNext                                        = &deviceFeatures;

		m_Device.CreateDevice(physicalDevice->Handle(), &createInfo);
		DEBUGUTILS_SETOBJECTNAME(m_Device, physicalDevice->GetProperties().deviceName)

		for (auto& [family, idItems] : queueFamilies)
		{
			int index = 0;
			for (auto& items : idItems | std::views::values)
			{
				for (size_t i = 0; i < items.size(); i++)
				{
					items[i] = m_Device.GetDeviceQueue(family, index);
					index++;
				}
			}
		}

#if 0 // Use One Queue for all commands. This method with higher fps.

		auto graphic     = queueFamilies[graphicFamily    ][0][0];
		auto present     = queueFamilies[presentFamily    ][0][0];
		auto compute     = queueFamilies[computeFamily    ][0][0];
		auto transfer    = queueFamilies[transferFamily   ][0][0];
		auto videoEncode = queueFamilies[videoEncodeFamily][4][0];
		auto videoDecode = queueFamilies[videoDecodeFamily][5][0];
		auto opticalFlow = queueFamilies[opticalFlowFamily][6][0];

#else // Split Commands to different Queues.

		auto graphic     = queueFamilies[graphicFamily    ][0][0];
		auto present     = queueFamilies[presentFamily    ][0][0];
		auto compute     = queueFamilies[computeFamily    ][2][0];
		auto transfer    = queueFamilies[transferFamily   ][3][0];
		auto videoEncode = queueFamilies[videoEncodeFamily][4][0];
		auto videoDecode = queueFamilies[videoDecodeFamily][5][0];
		auto opticalFlow = queueFamilies[opticalFlowFamily][6][0];

#endif

		GetContext().Registry<IGraphicQueue>(graphic);
		GetContext().Registry<IComputeQueue>(compute);
    	if (GetContext().Has<ISurface>())
    	{
    		GetContext().Registry<IPresentQueue>(present);
    	}

		GetContext().Registry<IGraphicThreadQueue>();
		GetContext().Registry<IComputeThreadQueue>();
		GetContext().Registry<ITransferThreadQueue>();
		GetContext().Registry<IVideoEncodeThreadQueue>();
		GetContext().Registry<IVideoDecodeThreadQueue>();
		GetContext().Registry<IOpticalFlowThreadQueue>();

		for (int i = 0; i < NThreadQueue; i++)
		{
			GetContext().Get<IGraphicThreadQueue>()->Add(queueFamilies[graphicFamily][0][i + 1]);
			GetContext().Get<IComputeThreadQueue>()->Add(queueFamilies[computeFamily][2][i + 1]);
		}

		GetContext().Get<ITransferThreadQueue>()->Add(transfer);
		GetContext().Get<IVideoEncodeThreadQueue>()->Add(videoEncode);
		GetContext().Get<IVideoDecodeThreadQueue>()->Add(videoDecode);
		GetContext().Get<IOpticalFlowThreadQueue>()->Add(opticalFlow);
    }

}

#endif