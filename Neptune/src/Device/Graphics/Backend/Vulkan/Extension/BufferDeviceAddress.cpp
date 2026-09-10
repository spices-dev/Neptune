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

        LinkToChain(pNext, filter, m_BufferDeviceAddressFeatures);
    }
    
    bool BufferDeviceAddress::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "BufferDeviceAddress [ bufferDeviceAddress ] : " << m_BufferDeviceAddressFeatures.bufferDeviceAddress;

        if (!m_BufferDeviceAddressFeatures.bufferDeviceAddress)
        {
            return false;
        }

        return true;
    }
}

#endif