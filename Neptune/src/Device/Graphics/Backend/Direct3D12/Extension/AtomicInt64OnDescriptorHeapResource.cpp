/**
* @file AtomicInt64OnDescriptorHeapResource.cpp.
* @brief The AtomicInt64OnDescriptorHeapResource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "AtomicInt64OnDescriptorHeapResource.h"

namespace Neptune::Direct3D12::Extension {
    
    bool AtomicInt64OnDescriptorHeapResource::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS11, &m_Options11, sizeof(m_Options11)))
        
        NEPTUNE_LOG_CORE(I) << "Options11 [ AtomicInt64OnDescriptorHeapResourceSupported ] : " << m_Options11.AtomicInt64OnDescriptorHeapResourceSupported;
        
        if (!m_Options11.AtomicInt64OnDescriptorHeapResourceSupported)
        {
            return false;
        }

        return true;
    }
}

#endif