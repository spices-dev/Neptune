/**
* @file ExecuteIndirect.cpp.
* @brief The ExecuteIndirect Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ExecuteIndirect.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ExecuteIndirect::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS21, &m_Options21, sizeof(m_Options21)))
        
        NEPTUNE_LOG_CORE(I) << "Options21 [ ExecuteIndirectTier ] : " << m_Options21.ExecuteIndirectTier;
        
        if (!m_Options21.ExecuteIndirectTier)
        {
            return false;
        }

        return true;
    }
}

#endif