/**
* @file MeshShaderFullRangeRenderTargetArrayIndex.cpp.
* @brief The MeshShaderFullRangeRenderTargetArrayIndex Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "MeshShaderFullRangeRenderTargetArrayIndex.h"

namespace Neptune::Direct3D12::Extension {
    
    bool MeshShaderFullRangeRenderTargetArrayIndex::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS9, &m_Options9, sizeof(m_Options9)))
        
        NEPTUNE_LOG_CORE(I) << "Options9 [ MeshShaderSupportsFullRangeRenderTargetArrayIndex ] : " << m_Options9.MeshShaderSupportsFullRangeRenderTargetArrayIndex;
        
        if (!m_Options9.MeshShaderSupportsFullRangeRenderTargetArrayIndex)
        {
            return false;
        }

        return true;
    }
}

#endif