/**
* @file Int64ShaderOps.cpp.
* @brief The Int64ShaderOps Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Int64ShaderOps.h"

namespace Neptune::Direct3D12::Extension {
    
    bool Int64ShaderOps::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &m_Options1, sizeof(m_Options1)))
        
        NEPTUNE_LOG_CORE(I) << "Options1 [ Int64ShaderOps ] : " << m_Options1.Int64ShaderOps;
        
        if (!m_Options1.Int64ShaderOps)
        {
            return false;
        }

        return true;
    }
}

#endif