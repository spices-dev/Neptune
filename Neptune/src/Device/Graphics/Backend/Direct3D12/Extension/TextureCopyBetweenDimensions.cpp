/**
* @file TextureCopyBetweenDimensions.cpp.
* @brief The TextureCopyBetweenDimensions Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "TextureCopyBetweenDimensions.h"

namespace Neptune::Direct3D12::Extension {
    
    bool TextureCopyBetweenDimensions::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS13, &m_Options13, sizeof(m_Options13)))
        
        NEPTUNE_LOG_CORE(I) << "Options13 [ TextureCopyBetweenDimensionsSupported ] : " << m_Options13.TextureCopyBetweenDimensionsSupported;
        
        if (!m_Options13.TextureCopyBetweenDimensionsSupported)
        {
            return false;
        }

        return true;
    }
}

#endif