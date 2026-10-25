/**
* @file ComputeOnlyWriteWatch.cpp.
* @brief The ComputeOnlyWriteWatch Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ComputeOnlyWriteWatch.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ComputeOnlyWriteWatch::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS20, &m_Options20, sizeof(m_Options20)))
        
        NEPTUNE_LOG_CORE(I) << "Options20 [ ComputeOnlyWriteWatchSupported ] : " << m_Options20.ComputeOnlyWriteWatchSupported;
        
        if (!m_Options20.ComputeOnlyWriteWatchSupported)
        {
            return false;
        }

        return true;
    }
}

#endif