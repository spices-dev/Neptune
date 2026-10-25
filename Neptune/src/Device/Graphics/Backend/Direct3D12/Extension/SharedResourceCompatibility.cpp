/**
* @file SharedResourceCompatibility.cpp.
* @brief The SharedResourceCompatibility Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "SharedResourceCompatibility.h"

namespace Neptune::Direct3D12::Extension {
    
    bool SharedResourceCompatibility::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS4, &m_Options4, sizeof(m_Options4)))
        
        NEPTUNE_LOG_CORE(I) << "Options4 [ SharedResourceCompatibilityTier ] : " << m_Options4.SharedResourceCompatibilityTier;
        
        if (!m_Options4.SharedResourceCompatibilityTier)
        {
            return false;
        }

        return true;
    }
}

#endif