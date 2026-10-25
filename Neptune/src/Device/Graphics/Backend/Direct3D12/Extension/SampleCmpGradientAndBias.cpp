/**
* @file SampleCmpGradientAndBias.cpp.
* @brief The SampleCmpGradientAndBias Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "SampleCmpGradientAndBias.h"

namespace Neptune::Direct3D12::Extension {
    
    bool SampleCmpGradientAndBias::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS21, &m_Options21, sizeof(m_Options21)))
        
        NEPTUNE_LOG_CORE(I) << "Options21 [ SampleCmpGradientAndBiasSupported ] : " << m_Options21.SampleCmpGradientAndBiasSupported;
        
        if (!m_Options21.SampleCmpGradientAndBiasSupported)
        {
            return false;
        }

        return true;
    }
}

#endif