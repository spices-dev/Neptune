/**
* @file MeshShader.cpp.
* @brief The MeshShader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "MeshShader.h"

namespace Neptune::Direct3D12::Extension {
    
    bool MeshShader::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &m_Options7, sizeof(m_Options7)))
        
        NEPTUNE_LOG_CORE(I) << "Options7 [ MeshShaderTier ] : " << m_Options7.MeshShaderTier;

        if (!m_Options7.MeshShaderTier)
        {
            return false;
        }

        return true;
    }
}

#endif