/**
* @file ShaderExecutionReorderingActuallyReorders.cpp.
* @brief The ShaderExecutionReorderingActuallyReorders Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ShaderExecutionReorderingActuallyReorders.h"

namespace Neptune::Direct3D12::Extension {
    
    bool ShaderExecutionReorderingActuallyReorders::IsFeaturesSatisfied(D3D12Device device)
    {
        NEPTUNE_PROFILE_ZONE
        
        DIRECT3D12_CHECK(device->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS22, &m_Options22, sizeof(m_Options22)))
        
        NEPTUNE_LOG_CORE(I) << "Options22 [ ShaderExecutionReorderingActuallyReorders ] : " << m_Options22.ShaderExecutionReorderingActuallyReorders;
        
        if (!m_Options22.ShaderExecutionReorderingActuallyReorders)
        {
            return false;
        }

        return true;
    }
}

#endif