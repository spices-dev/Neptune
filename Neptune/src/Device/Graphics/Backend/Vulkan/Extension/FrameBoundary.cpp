/**
* @file FrameBoundary.cpp.
* @brief The FrameBoundary Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "FrameBoundary.h"

namespace Neptune::Vulkan::Extension {

    FrameBoundary::FrameBoundary(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_FRAME_BOUNDARY_EXTENSION_NAME);
    }
    
    void FrameBoundary::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_FrameBoundaryFeatures);
    }
    
    bool FrameBoundary::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "FrameBoundary [ frameBoundary ] : " << m_FrameBoundaryFeatures.frameBoundary;

        if (!m_FrameBoundaryFeatures.frameBoundary)
        {
            return false;
        }
        
        return true;
    }

}

#endif