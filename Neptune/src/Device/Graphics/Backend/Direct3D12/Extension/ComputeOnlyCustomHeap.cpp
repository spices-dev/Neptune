/**
* @file ComputeOnlyCustomHeap.cpp.
* @brief The ComputeOnlyCustomHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ComputeOnlyCustomHeap.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ComputeOnlyCustomHeap::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS19, &m_Options19, sizeof(m_Options19)))
        
        NEPTUNE_LOG_CORE(I) << "Options19 [ ComputeOnlyCustomHeapSupported ] : " << m_Options19.ComputeOnlyCustomHeapSupported;
        
        if (!m_Options19.ComputeOnlyCustomHeapSupported)
        {
            return false;
        }

        return true;
    }
}

#endif