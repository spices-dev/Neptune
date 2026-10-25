/**
* @file AtomicInt64OnTypedResource.cpp.
* @brief The AtomicInt64OnTypedResource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "AtomicInt64OnTypedResource.h"

namespace Neptune::Direct3D12::Extension {
    
    bool AtomicInt64OnTypedResource::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS9, &m_Options9, sizeof(m_Options9)))
        
        NEPTUNE_LOG_CORE(I) << "Options9 [ AtomicInt64OnTypedResourceSupported ] : " << m_Options9.AtomicInt64OnTypedResourceSupported;
        
        if (!m_Options9.AtomicInt64OnTypedResourceSupported)
        {
            return false;
        }

        return true;
    }
}

#endif