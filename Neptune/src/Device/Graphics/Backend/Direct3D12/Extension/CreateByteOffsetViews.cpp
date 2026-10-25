/**
* @file CreateByteOffsetViews.cpp.
* @brief The CreateByteOffsetViews Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "CreateByteOffsetViews.h"

namespace Neptune::Direct3D12::Extension {
    
    bool CreateByteOffsetViews::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS22, &m_Options22, sizeof(m_Options22)))
        
        NEPTUNE_LOG_CORE(I) << "Options22 [ CreateByteOffsetViewsSupported ] : " << m_Options22.CreateByteOffsetViewsSupported;
        
        if (!m_Options22.CreateByteOffsetViewsSupported)
        {
            return false;
        }

        return true;
    }
}

#endif