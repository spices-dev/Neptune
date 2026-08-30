/**
* @file NgfxCapture.cpp.
* @brief The NgfxCapture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "NgfxCapture.h"

namespace Neptune::Vulkan::Layer {

    NgfxCapture::NgfxCapture(ELayerState state)
        : Layer("VK_LAYER_NV_ngfx_capture_release_public_2026_3_0", state)
    {}

}

#endif