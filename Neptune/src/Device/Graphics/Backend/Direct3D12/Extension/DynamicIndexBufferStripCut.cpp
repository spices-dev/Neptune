/**
* @file DynamicIndexBufferStripCut.cpp.
* @brief The DynamicIndexBufferStripCut Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DynamicIndexBufferStripCut.h"

namespace Neptune::Direct3D12::Extension {
    
    bool DynamicIndexBufferStripCut::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS15, &m_Options15, sizeof(m_Options15)))
        
        NEPTUNE_LOG_CORE(I) << "Options15 [ DynamicIndexBufferStripCutSupported ] : " << m_Options15.DynamicIndexBufferStripCutSupported;
        
        if (!m_Options15.DynamicIndexBufferStripCutSupported)
        {
            return false;
        }

        return true;
    }
}

#endif