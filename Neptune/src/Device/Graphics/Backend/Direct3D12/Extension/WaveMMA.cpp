/**
* @file WaveMMA.cpp.
* @brief The WaveMMA Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "WaveMMA.h"

namespace Neptune::Direct3D12::Extension {
    
    bool WaveMMA::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS9, &m_Options9, sizeof(m_Options9)))
        
        NEPTUNE_LOG_CORE(I) << "Options9 [ WaveMMATier ] : " << m_Options9.WaveMMATier;
        
        if (!m_Options9.WaveMMATier)
        {
            return false;
        }

        return true;
    }
}

#endif