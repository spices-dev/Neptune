/**
* @file WriteableMSAATextures.cpp.
* @brief The WriteableMSAATextures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "WriteableMSAATextures.h"

namespace Neptune::Direct3D12::Extension {
    
    bool WriteableMSAATextures::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS14, &m_Options14, sizeof(m_Options14)))
        
        NEPTUNE_LOG_CORE(I) << "Options14 [ WriteableMSAATexturesSupported ] : " << m_Options14.WriteableMSAATexturesSupported;
        
        if (!m_Options14.WriteableMSAATexturesSupported)
        {
            return false;
        }

        return true;
    }
}

#endif