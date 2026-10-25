/**
* @file AtomicInt64OnGroupShared.cpp.
* @brief The AtomicInt64OnGroupShared Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "AtomicInt64OnGroupShared.h"

namespace Neptune::Direct3D12::Extension {
    
    bool AtomicInt64OnGroupShared::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS9, &m_Options9, sizeof(m_Options9)))
        
        NEPTUNE_LOG_CORE(I) << "Options9 [ AtomicInt64OnGroupSharedSupported ] : " << m_Options9.AtomicInt64OnGroupSharedSupported;
        
        if (!m_Options9.AtomicInt64OnGroupSharedSupported)
        {
            return false;
        }

        return true;
    }
}

#endif