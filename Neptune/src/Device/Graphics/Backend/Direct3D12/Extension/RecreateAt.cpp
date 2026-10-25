/**
* @file RecreateAt.cpp.
* @brief The RecreateAt Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RecreateAt.h"

namespace Neptune::Direct3D12::Extension {
    
    bool RecreateAt::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS20, &m_Options20, sizeof(m_Options20)))
        
        NEPTUNE_LOG_CORE(I) << "Options20 [ RecreateAtTier ] : " << m_Options20.RecreateAtTier;
        
        if (!m_Options20.RecreateAtTier)
        {
            return false;
        }

        return true;
    }
}

#endif