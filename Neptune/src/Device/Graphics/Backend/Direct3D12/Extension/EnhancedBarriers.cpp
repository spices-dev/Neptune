/**
* @file EnhancedBarriers.cpp.
* @brief The EnhancedBarriers Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "EnhancedBarriers.h"

namespace Neptune::Direct3D12::Extension {
    
    bool EnhancedBarriers::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS12, &m_Options12, sizeof(m_Options12)))
        
        NEPTUNE_LOG_CORE(I) << "Options12 [ EnhancedBarriersSupported ] : " << m_Options12.EnhancedBarriersSupported;
        
        if (!m_Options12.EnhancedBarriersSupported)
        {
            return false;
        }

        return true;
    }
}

#endif