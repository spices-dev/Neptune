/**
* @file RasterizerDesc2.cpp.
* @brief The RasterizerDesc2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RasterizerDesc2.h"

namespace Neptune::Direct3D12::Extension {
    
    bool RasterizerDesc2::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS19, &m_Options19, sizeof(m_Options19)))
        
        NEPTUNE_LOG_CORE(I) << "Options19 [ RasterizerDesc2Supported ] : " << m_Options19.RasterizerDesc2Supported;
        
        if (!m_Options19.RasterizerDesc2Supported)
        {
            return false;
        }

        return true;
    }
}

#endif