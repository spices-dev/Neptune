/**
* @file ViewInstancing.cpp.
* @brief The ViewInstancing Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ViewInstancing.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ViewInstancing::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS3, &m_Options3, sizeof(m_Options3)))
        
        NEPTUNE_LOG_CORE(I) << "Options3 [ ViewInstancingTier ] : " << m_Options3.ViewInstancingTier;
        
        if (!m_Options3.ViewInstancingTier)
        {
            return false;
        }

        return true;
    }
}

#endif