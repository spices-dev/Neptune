/**
* @file GPUUploadHeap.cpp.
* @brief The GPUUploadHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "GPUUploadHeap.h"

namespace Neptune::Direct3D12::Extension {
    
    bool GPUUploadHeap::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS16, &m_Options16, sizeof(m_Options16)))
        
        NEPTUNE_LOG_CORE(I) << "Options16 [ GPUUploadHeapSupported ] : " << m_Options16.GPUUploadHeapSupported;
        
        if (!m_Options16.GPUUploadHeapSupported)
        {
            return false;
        }

        return true;
    }
}

#endif