/**
* @file WorkGraphs.cpp.
* @brief The WorkGraphs Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "WorkGraphs.h"

namespace Neptune::Direct3D12::Extension {
    
    bool WorkGraphs::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS21, &m_Options21, sizeof(m_Options21)))
        
        NEPTUNE_LOG_CORE(I) << "Options21 [ WorkGraphsTier ] : " << m_Options21.WorkGraphsTier;
        
        if (!m_Options21.WorkGraphsTier)
        {
            return false;
        }

        return true;
    }
}

#endif