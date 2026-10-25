/**
* @file ManualWriteTrackingResource.cpp.
* @brief The ManualWriteTrackingResource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ManualWriteTrackingResource.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ManualWriteTrackingResource::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS17, &m_Options17, sizeof(m_Options17)))
        
        NEPTUNE_LOG_CORE(I) << "Options17 [ ManualWriteTrackingResourceSupported ] : " << m_Options17.ManualWriteTrackingResourceSupported;
        
        if (!m_Options17.ManualWriteTrackingResourceSupported)
        {
            return false;
        }

        return true;
    }
}

#endif