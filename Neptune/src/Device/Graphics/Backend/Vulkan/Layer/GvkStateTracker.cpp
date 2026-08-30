/**
* @file GvkStateTracker.cpp.
* @brief The GvkStateTracker Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GvkStateTracker.h"

namespace Neptune::Vulkan::Layer {

    GvkStateTracker::GvkStateTracker(ELayerState state)
        : Layer("VK_LAYER_INTEL_gvk_state_tracker", state)
    {}

}

#endif