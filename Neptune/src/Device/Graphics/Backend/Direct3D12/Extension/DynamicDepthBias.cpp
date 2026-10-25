/**
* @file DynamicDepthBias.cpp.
* @brief The DynamicDepthBias Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DynamicDepthBias.h"

namespace Neptune::Direct3D12::Extension {
    
    bool DynamicDepthBias::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS16, &m_Options16, sizeof(m_Options16)))
        
        NEPTUNE_LOG_CORE(I) << "Options16 [ DynamicDepthBiasSupported ] : " << m_Options16.DynamicDepthBiasSupported;
        
        if (!m_Options16.DynamicDepthBiasSupported)
        {
            return false;
        }

        return true;
    }
}

#endif