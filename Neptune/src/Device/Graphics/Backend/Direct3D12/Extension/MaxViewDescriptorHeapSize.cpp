/**
* @file MaxViewDescriptorHeapSize.cpp.
* @brief The MaxViewDescriptorHeapSize Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "MaxViewDescriptorHeapSize.h"

namespace Neptune::Direct3D12::Extension {
    
    bool MaxViewDescriptorHeapSize::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS19, &m_Options19, sizeof(m_Options19)))
        
        NEPTUNE_LOG_CORE(I) << "Options19 [ MaxViewDescriptorHeapSize ] : " << m_Options19.MaxViewDescriptorHeapSize;
        
        if (!m_Options19.MaxViewDescriptorHeapSize)
        {
            return false;
        }

        return true;
    }
}

#endif