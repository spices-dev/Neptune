/**
* @file MSPrimitivesPipelineStatisticIncludesCulledPrimitives.cpp.
* @brief The MSPrimitivesPipelineStatisticIncludesCulledPrimitives Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "MSPrimitivesPipelineStatisticIncludesCulledPrimitives.h"

namespace Neptune::Direct3D12::Extension {
    
    bool MSPrimitivesPipelineStatisticIncludesCulledPrimitives::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS12, &m_Options12, sizeof(m_Options12)))
        
        NEPTUNE_LOG_CORE(I) << "Options12 [ MSPrimitivesPipelineStatisticIncludesCulledPrimitives ] : " << m_Options12.MSPrimitivesPipelineStatisticIncludesCulledPrimitives;
        
        if (!m_Options12.MSPrimitivesPipelineStatisticIncludesCulledPrimitives)
        {
            return false;
        }

        return true;
    }
}

#endif