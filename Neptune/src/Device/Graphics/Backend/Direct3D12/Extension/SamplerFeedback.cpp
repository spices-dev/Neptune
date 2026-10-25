/**
* @file SamplerFeedback.cpp.
* @brief The SamplerFeedback Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "SamplerFeedback.h"

namespace Neptune::Direct3D12::Extension {
    
    bool SamplerFeedback::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &m_Options7, sizeof(m_Options7)))
        
        NEPTUNE_LOG_CORE(I) << "Options7 [ SamplerFeedbackTier ] : " << m_Options7.SamplerFeedbackTier;

        if (!m_Options7.SamplerFeedbackTier)
        {
            return false;
        }

        return true;
    }
}

#endif