/**
* @file Barycentrics.cpp.
* @brief The Barycentrics Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Barycentrics.h"

namespace Neptune::Direct3D12::Extension {
    
    bool Barycentrics::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS3, &m_Options3, sizeof(m_Options3)))
        
        NEPTUNE_LOG_CORE(I) << "Options3 [ BarycentricsSupported ] : " << m_Options3.BarycentricsSupported;
        
        if (!m_Options3.BarycentricsSupported)
        {
            return false;
        }

        return true;
    }
}

#endif