/**
* @file GPUTrace.cpp.
* @brief The GPUTrace Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GPUTrace.h"

namespace Neptune::Vulkan::Layer {

    GPUTrace::GPUTrace(ELayerState state)
        : Layer("VK_LAYER_NV_GPU_Trace_release_public_2026_3_0", state)
    {}

}

#endif