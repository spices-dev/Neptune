/**
* @file Extensions.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Extensions.h"
#include "Device/Graphics/Backend/Vulkan/Extension/ExtensionHeader.h"
#include "Window/Window.h"

namespace Neptune::Vulkan {

	Extensions::Extensions(Context& context, EInfrastructure e, const Window* window)
		: Infrastructure(context, e)
	{
		NEPTUNE_PROFILE_ZONE

		Create(window);
	}

	void Extensions::Create(const Window* window)
	{
		NEPTUNE_PROFILE_ZONE
		
		if (window)
		{
			m_Context.Registry<Extension::ISwapChain>(Extension::EExtensionState::Core, window->Extension());
		}
		else
		{
			m_Context.Registry<Extension::ISwapChain>(Extension::EExtensionState::Extent, std::vector{ VK_KHR_SURFACE_EXTENSION_NAME });
		}
		
#ifdef NEPTUNE_DEBUG
		
		m_Context.Registry<Extension::IDebugUtils>                       (Extension::EExtensionState::Extent);
		
#endif
		
		m_Context.Registry<Extension::IDescriptorHeap>                   (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDescriptorBuffer>                 (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDeviceFault>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IMemoryBudget>                     (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IHDR>                              (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IOpticalFlow>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IRayTracing>                       (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IVideoDecode>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IVideoEncode>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ISamplerYcbcrConversion>           (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IMaintenance1>                     (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IBufferDeviceAddress>              (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDescriptorIndexing>               (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IVulkan13>                         (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IPortability>                      (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IQueue>                            (Extension::EExtensionState::Core);
		m_Context.Registry<Extension::ILayerSetting>                     (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDynamicRendering>                 (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDeviceGeneratedCommands>          (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IGetPhysicalDeviceProperties2>     (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IPageableDeviceLocalMemory>        (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IGetSurfaceCapabilities2>          (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::ICreateRenderPass2>                (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IDynamicRenderingLocalRead>        (Extension::EExtensionState::Extent);
		m_Context.Registry<Extension::IScalarBlockLayout>                (Extension::EExtensionState::Core);
		m_Context.Registry<Extension::ITimelineSemaphore>                (Extension::EExtensionState::Core);
		m_Context.Registry<Extension::ISynchronization2>                 (Extension::EExtensionState::Core);
	}
	
	void Extensions::BuildFeatureChain(void** pNext)
	{
		NEPTUNE_PROFILE_ZONE
		
		std::function filter = [](VkStructureType){ return true; };
		
		m_Context.View([&](const auto e, const auto& extension) {

			auto last = pNext;
			
			extension->BuildFeatureChain(pNext, filter);

			pNext = pNext ? pNext : last;
		});
	}
	
	void Extensions::BuildFeatureChainWithoutRepeat(void** pNext)
	{
		NEPTUNE_PROFILE_ZONE
		
		std::unordered_set<VkStructureType> linked;
		
		std::function filter = [&](VkStructureType type) {
			
			if (linked.contains(type)) return false;
			
			linked.insert(type);
			
			return true;
		};
		
		m_Context.View([&](const auto e, const auto& extension) {

			auto last = pNext;
			
			extension->BuildFeatureChain(pNext, filter);

			pNext = pNext ? pNext : last;
		});
	}

	void Extensions::BuildPropertyChain(void** pNext)
	{
		NEPTUNE_PROFILE_ZONE
		
		std::function filter = [](VkStructureType){ return true; };
		
		m_Context.View([&](const auto e, const auto& extension) {

			auto last = pNext;
			
			extension->BuildPropertyChain(pNext, filter);

			pNext = pNext ? pNext : last;
		});
	}
	
	std::unordered_set<VkQueueFlagBits> Extensions::BuildQueueChain(const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const
	{
		NEPTUNE_PROFILE_ZONE
		
		const auto& queue = m_Context.Get<Extension::IQueue>();
		
		return queue->Query(device, surface);
	}
}

#endif