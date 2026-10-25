/**
* @file MeshShaderPerPrimitiveShadingRate.cpp.
* @brief The MeshShaderPerPrimitiveShadingRate Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "MeshShaderPerPrimitiveShadingRate.h"

namespace Neptune::Direct3D12::Extension {
    
    bool MeshShaderPerPrimitiveShadingRate::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS10, &m_Options10, sizeof(m_Options10)))
        
        NEPTUNE_LOG_CORE(I) << "Options10 [ MeshShaderPerPrimitiveShadingRateSupported ] : " << m_Options10.MeshShaderPerPrimitiveShadingRateSupported;
        
        if (!m_Options10.MeshShaderPerPrimitiveShadingRateSupported)
        {
            return false;
        }

        return true;
    }
}

#endif