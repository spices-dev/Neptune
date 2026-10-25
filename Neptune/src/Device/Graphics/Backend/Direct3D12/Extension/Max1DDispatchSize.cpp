/**
* @file Max1DDispatchSize.cpp.
* @brief The Max1DDispatchSize Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Max1DDispatchSize.h"

namespace Neptune::Direct3D12::Extension {
    
    bool Max1DDispatchSize::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS22, &m_Options22, sizeof(m_Options22)))
        
        NEPTUNE_LOG_CORE(I) << "Options22 [ Max1DDispatchSize ] : " << m_Options22.Max1DDispatchSize;
        
        if (!m_Options22.Max1DDispatchSize)
        {
            return false;
        }

        return true;
    }
}

#endif