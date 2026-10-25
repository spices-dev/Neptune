/**
* @file NonNormalizedCoordinateSamplers.cpp.
* @brief The NonNormalizedCoordinateSamplers Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "NonNormalizedCoordinateSamplers.h"

namespace Neptune::Direct3D12::Extension {
    
    bool NonNormalizedCoordinateSamplers::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS17, &m_Options17, sizeof(m_Options17)))
        
        NEPTUNE_LOG_CORE(I) << "Options17 [ NonNormalizedCoordinateSamplersSupported ] : " << m_Options17.NonNormalizedCoordinateSamplersSupported;
        
        if (!m_Options17.NonNormalizedCoordinateSamplersSupported)
        {
            return false;
        }

        return true;
    }
}

#endif