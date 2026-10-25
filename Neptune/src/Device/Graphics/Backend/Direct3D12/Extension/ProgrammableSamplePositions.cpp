/**
* @file ProgrammableSamplePositions.cpp.
* @brief The ProgrammableSamplePositions Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ProgrammableSamplePositions.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ProgrammableSamplePositions::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS2, &m_Options2, sizeof(m_Options2)))
        
        NEPTUNE_LOG_CORE(I) << "Options2 [ ProgrammableSamplePositionsTier ] : " << m_Options2.ProgrammableSamplePositionsTier;
        
        if (!m_Options2.ProgrammableSamplePositionsTier)
        {
            return false;
        }

        return true;
    }
}

#endif