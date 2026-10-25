/**
* @file InvertedViewportHeightFlipsY.cpp.
* @brief The InvertedViewportHeightFlipsY Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "InvertedViewportHeightFlipsY.h"

namespace Neptune::Direct3D12::Extension {
    
    bool InvertedViewportHeightFlipsY::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS13, &m_Options13, sizeof(m_Options13)))
        
        NEPTUNE_LOG_CORE(I) << "Options13 [ InvertedViewportHeightFlipsYSupported ] : " << m_Options13.InvertedViewportHeightFlipsYSupported;
        
        if (!m_Options13.InvertedViewportHeightFlipsYSupported)
        {
            return false;
        }

        return true;
    }
}

#endif