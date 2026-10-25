/**
* @file WaveOps.cpp.
* @brief The WaveOps Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "WaveOps.h"

namespace Neptune::Direct3D12::Extension {
    
    bool WaveOps::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &m_Options1, sizeof(m_Options1)))
        
        NEPTUNE_LOG_CORE(I) << "Options1 [ WaveOps ] : " << m_Options1.WaveOps;
        NEPTUNE_LOG_CORE(I) << "Options1 [ WaveLaneCountMin ] : " << m_Options1.WaveLaneCountMin;
        NEPTUNE_LOG_CORE(I) << "Options1 [ WaveLaneCountMax ] : " << m_Options1.WaveLaneCountMax;
        NEPTUNE_LOG_CORE(I) << "Options1 [ TotalLaneCount ] : " << m_Options1.TotalLaneCount;
        
        if (!m_Options1.WaveOps)
        {
            return false;
        }

        return true;
    }
}

#endif