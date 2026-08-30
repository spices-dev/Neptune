/**
* @file Nomad.cpp.
* @brief The Nomad Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Nomad.h"

namespace Neptune::Vulkan::Layer {

    Nomad::Nomad(ELayerState state)
        : Layer("VK_LAYER_NV_nomad_release_public_2026_3_0", state)
    {}

}

#endif