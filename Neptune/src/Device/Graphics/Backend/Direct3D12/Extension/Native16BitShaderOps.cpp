/**
* @file Native16BitShaderOps.cpp.
* @brief The Native16BitShaderOps Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Native16BitShaderOps.h"

namespace Neptune::Direct3D12::Extension {
    
    bool Native16BitShaderOps::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS4, &m_Options4, sizeof(m_Options4)))
        
        NEPTUNE_LOG_CORE(I) << "Options4 [ Native16BitShaderOpsSupported ] : " << m_Options4.Native16BitShaderOpsSupported;

        if (!m_Options4.Native16BitShaderOpsSupported)
        {
            return false;
        }

        return true;
    }
}

#endif