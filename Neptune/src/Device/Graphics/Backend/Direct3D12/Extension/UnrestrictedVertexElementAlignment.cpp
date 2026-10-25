/**
* @file UnrestrictedVertexElementAlignment.cpp.
* @brief The UnrestrictedVertexElementAlignment Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "UnrestrictedVertexElementAlignment.h"

namespace Neptune::Direct3D12::Extension {
    
    bool UnrestrictedVertexElementAlignment::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS13, &m_Options13, sizeof(m_Options13)))
        
        NEPTUNE_LOG_CORE(I) << "Options13 [ UnrestrictedVertexElementAlignmentSupported ] : " << m_Options13.UnrestrictedVertexElementAlignmentSupported;
        
        if (!m_Options13.UnrestrictedVertexElementAlignmentSupported)
        {
            return false;
        }

        return true;
    }
}

#endif