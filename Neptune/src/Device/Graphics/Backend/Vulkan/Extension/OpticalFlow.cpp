/**
* @file OpticalFlow.cpp.
* @brief The OpticalFlow Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "OpticalFlow.h"

namespace Neptune::Vulkan::Extension {
    
    OpticalFlow::OpticalFlow()
    {
        NEPTUNE_PROFILE_ZONE
        
        AddDeviceExtensions(VK_NV_OPTICAL_FLOW_EXTENSION_NAME);
    }
    
}

#endif