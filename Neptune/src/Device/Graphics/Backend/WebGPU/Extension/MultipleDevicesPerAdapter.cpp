/**
* @file MultipleDevicesPerAdapter.cpp.
* @brief The MultipleDevicesPerAdapter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "MultipleDevicesPerAdapter.h"

namespace Neptune::WebGPU::Extension {
    
    MultipleDevicesPerAdapter::MultipleDevicesPerAdapter(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        AddInstanceFeatures(WGPUInstanceFeatureName_MultipleDevicesPerAdapter);
    }
}

#endif