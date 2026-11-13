/**
* @file PushDescriptor.cpp.
* @brief The PushDescriptor Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "PushDescriptor.h"

namespace Neptune::Vulkan::Extension {
    
    PushDescriptor::PushDescriptor(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME);
    }
    
    void PushDescriptor::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_Vulkan14Features);
    }
    
    bool PushDescriptor::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "Vulkan14 [ pushDescriptor ] : " << m_Vulkan14Features.pushDescriptor;

        if (!m_Vulkan14Features.pushDescriptor)
        {
            return false;
        }
        
        return true;
    }
}

#endif