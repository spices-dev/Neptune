/**
* @file BackgroundProcessing.cpp.
* @brief The BackgroundProcessing Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "BackgroundProcessing.h"

namespace Neptune::Direct3D12::Extension {
    
    bool BackgroundProcessing::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &m_Options6, sizeof(m_Options6)))
        
        NEPTUNE_LOG_CORE(I) << "Options6 [ BackgroundProcessingSupported ] : " << m_Options6.BackgroundProcessingSupported;
        
        if (!m_Options6.BackgroundProcessingSupported)
        {
            return false;
        }

        return true;
    }
}

#endif