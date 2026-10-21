/**
* @file BufferDeviceAddress.cpp.
* @brief The BufferDeviceAddress Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "BufferDeviceAddress.h"

namespace Neptune::Vulkan::Extension {
    
    void BufferDeviceAddress::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan12Features);
    }
    
    bool BufferDeviceAddress::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan12 [ bufferDeviceAddress ] : " << m_Vulkan12Features.bufferDeviceAddress;

        if (!m_Vulkan12Features.bufferDeviceAddress)
        {
            return false;
        }

        return true;
    }
}

#endif