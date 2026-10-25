/**
* @file SRVOnlyTiledResource.cpp.
* @brief The SRVOnlyTiledResource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "SRVOnlyTiledResource.h"

namespace Neptune::Direct3D12::Extension {
    
    bool SRVOnlyTiledResource::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &m_Options5, sizeof(m_Options5)))
        
        NEPTUNE_LOG_CORE(I) << "Options5 [ SRVOnlyTiledResourceTier3 ] : " << m_Options5.SRVOnlyTiledResourceTier3;
        
        if (!m_Options5.SRVOnlyTiledResourceTier3)
        {
            return false;
        }

        return true;
    }
}

#endif