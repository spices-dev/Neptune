/**
* @file UnifiedImageLayouts.cpp.
* @brief The UnifiedImageLayouts Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "UnifiedImageLayouts.h"

namespace Neptune::Vulkan::Extension {
    
    UnifiedImageLayouts::UnifiedImageLayouts(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE
        
        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME);
    }
    
    void UnifiedImageLayouts::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_UnifiedImageLayoutsFeatures);
    }
    
    bool UnifiedImageLayouts::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "UnifiedImageLayouts [ unifiedImageLayouts ] : " << m_UnifiedImageLayoutsFeatures.unifiedImageLayouts;
        NEPTUNE_LOG_CORE(I) << "UnifiedImageLayouts [ unifiedImageLayoutsVideo ] : " << m_UnifiedImageLayoutsFeatures.unifiedImageLayoutsVideo;
        
        if (!m_UnifiedImageLayoutsFeatures.unifiedImageLayouts)
        {
            return false;
        }
        
        if (!m_UnifiedImageLayoutsFeatures.unifiedImageLayoutsVideo)
        {
            return false;
        }

        return true;
    }
}

#endif