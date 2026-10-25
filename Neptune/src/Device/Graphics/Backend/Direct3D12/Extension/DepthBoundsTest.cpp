/**
* @file DepthBoundsTest.cpp.
* @brief The DepthBoundsTest Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DepthBoundsTest.h"

namespace Neptune::Direct3D12::Extension {
    
    bool DepthBoundsTest::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS2, &m_Options2, sizeof(m_Options2)))
        
        NEPTUNE_LOG_CORE(I) << "Options2 [ DepthBoundsTestSupported ] : " << m_Options2.DepthBoundsTestSupported;
        
        if (!m_Options2.DepthBoundsTestSupported)
        {
            return false;
        }

        return true;
    }
}

#endif