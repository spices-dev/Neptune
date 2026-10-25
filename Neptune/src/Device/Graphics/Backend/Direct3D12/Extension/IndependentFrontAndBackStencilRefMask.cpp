/**
* @file IndependentFrontAndBackStencilRefMask.cpp.
* @brief The IndependentFrontAndBackStencilRefMask Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "IndependentFrontAndBackStencilRefMask.h"

namespace Neptune::Direct3D12::Extension {
    
    bool IndependentFrontAndBackStencilRefMask::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS14, &m_Options14, sizeof(m_Options14)))
        
        NEPTUNE_LOG_CORE(I) << "Options14 [ IndependentFrontAndBackStencilRefMaskSupported ] : " << m_Options14.IndependentFrontAndBackStencilRefMaskSupported;
        
        if (!m_Options14.IndependentFrontAndBackStencilRefMaskSupported)
        {
            return false;
        }

        return true;
    }
}

#endif