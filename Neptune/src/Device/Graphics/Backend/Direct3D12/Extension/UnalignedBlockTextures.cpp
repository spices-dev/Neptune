/**
* @file UnalignedBlockTextures.cpp.
* @brief The UnalignedBlockTextures Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "UnalignedBlockTextures.h"

namespace Neptune::Direct3D12::Extension {
    
    bool UnalignedBlockTextures::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS8, &m_Options8, sizeof(m_Options8)))
        
        NEPTUNE_LOG_CORE(I) << "Options8 [ UnalignedBlockTexturesSupported ] : " << m_Options8.UnalignedBlockTexturesSupported;
        
        if (!m_Options8.UnalignedBlockTexturesSupported)
        {
            return false;
        }

        return true;
    }
}

#endif