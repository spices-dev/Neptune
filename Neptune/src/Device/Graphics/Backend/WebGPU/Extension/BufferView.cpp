/**
* @file BufferView.cpp.
* @brief The BufferView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "BufferView.h"

namespace Neptune::WebGPU::Extension {
    
    BufferView::BufferView(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddWGSLFeatures(WGPUWGSLLanguageFeatureName_BufferView);
    }
}

#endif