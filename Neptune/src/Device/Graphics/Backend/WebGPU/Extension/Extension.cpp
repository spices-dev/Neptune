/**
* @file Extension.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Extension.h"

namespace Neptune::WebGPU::Extension {
    
    void Extension::AddInstanceFeatures(WGPUInstanceFeatureName name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_InstanceFeatures.insert_or_assign(name, value);
    }
    
    void Extension::AddWGSLFeatures(const WGPUWGSLLanguageFeatureName name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_WGSLFeatures.insert_or_assign(name, value);
    }
    
}

#endif