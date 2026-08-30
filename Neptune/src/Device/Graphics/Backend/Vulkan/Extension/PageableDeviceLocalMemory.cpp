/**
* @file PageableDeviceLocalMemory.cpp.
* @brief The PageableDeviceLocalMemory Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PageableDeviceLocalMemory.h"

namespace Neptune::Vulkan::Extension {

    PageableDeviceLocalMemory::PageableDeviceLocalMemory(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddDeviceExtensions(VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME);
        AddDeviceExtensions(VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_EXTENSION_NAME);
    }

    void PageableDeviceLocalMemory::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        if (std::invoke(filter, m_PageableDeviceLocalMemoryFeatures.sType))
        {
            *pNext = &m_PageableDeviceLocalMemoryFeatures;

            pNext  = &m_PageableDeviceLocalMemoryFeatures.pNext;
        }
    }
    
    bool PageableDeviceLocalMemory::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "PageableDeviceLocalMemory [ pageableDeviceLocalMemory ] : " << m_PageableDeviceLocalMemoryFeatures.pageableDeviceLocalMemory;
        
        if (!m_PageableDeviceLocalMemoryFeatures.pageableDeviceLocalMemory)
        {
            return false;
        }

        return true;
    }

}

#endif