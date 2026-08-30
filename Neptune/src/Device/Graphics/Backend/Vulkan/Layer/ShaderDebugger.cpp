/**
* @file ShaderDebugger.cpp.
* @brief The ShaderDebugger Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "ShaderDebugger.h"

namespace Neptune::Vulkan::Layer {

    ShaderDebugger::ShaderDebugger(ELayerState state)
        : Layer("VK_LAYER_NV_shader_debugger_release_public_2026_3_0", state)
    {}

}

#endif