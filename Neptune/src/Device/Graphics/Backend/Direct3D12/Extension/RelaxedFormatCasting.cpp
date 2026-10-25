/**
* @file RelaxedFormatCasting.cpp.
* @brief The RelaxedFormatCasting Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RelaxedFormatCasting.h"

namespace Neptune::Direct3D12::Extension {
    
    bool RelaxedFormatCasting::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS12, &m_Options12, sizeof(m_Options12)))
        
        NEPTUNE_LOG_CORE(I) << "Options12 [ RelaxedFormatCastingSupported ] : " << m_Options12.RelaxedFormatCastingSupported;
        
        if (!m_Options12.RelaxedFormatCastingSupported)
        {
            return false;
        }

        return true;
    }
}

#endif