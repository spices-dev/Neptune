/**
* @file RenderPasses.cpp.
* @brief The RenderPasses Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RenderPasses.h"

namespace Neptune::Direct3D12::Extension {
    
    bool RenderPasses::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &m_Options5, sizeof(m_Options5)))
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS18, &m_Options18, sizeof(m_Options18)))
        
        NEPTUNE_LOG_CORE(I) << "Options5 [ RenderPassesTier ] : " << m_Options5.RenderPassesTier;
        NEPTUNE_LOG_CORE(I) << "Options18 [ RenderPassesValid ] : " << m_Options18.RenderPassesValid;

        if (!m_Options18.RenderPassesValid)
        {
            return false;
        }

        return true;
    }
}

#endif