/**
* @file NarrowQuadrilateralLines.cpp.
* @brief The NarrowQuadrilateralLines Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "NarrowQuadrilateralLines.h"

namespace Neptune::Direct3D12::Extension {
    
    bool NarrowQuadrilateralLines::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS19, &m_Options19, sizeof(m_Options19)))
        
        NEPTUNE_LOG_CORE(I) << "Options19 [ NarrowQuadrilateralLinesSupported ] : " << m_Options19.NarrowQuadrilateralLinesSupported;
        
        if (!m_Options19.NarrowQuadrilateralLinesSupported)
        {
            return false;
        }

        return true;
    }
}

#endif