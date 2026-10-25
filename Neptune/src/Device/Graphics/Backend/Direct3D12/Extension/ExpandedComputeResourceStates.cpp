/**
* @file ExpandedComputeResourceStates.cpp.
* @brief The ExpandedComputeResourceStates Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ExpandedComputeResourceStates.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ExpandedComputeResourceStates::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &m_Options1, sizeof(m_Options1)))
        
        NEPTUNE_LOG_CORE(I) << "Options1 [ ExpandedComputeResourceStates ] : " << m_Options1.ExpandedComputeResourceStates;
        
        if (!m_Options1.ExpandedComputeResourceStates)
        {
            return false;
        }

        return true;
    }
}

#endif