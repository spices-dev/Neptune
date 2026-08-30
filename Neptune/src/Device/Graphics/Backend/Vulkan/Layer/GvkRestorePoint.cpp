/**
* @file GvkRestorePoint.cpp.
* @brief The GvkRestorePoint Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "GvkRestorePoint.h"

namespace Neptune::Vulkan::Layer {

    GvkRestorePoint::GvkRestorePoint(ELayerState state)
        : Layer("VK_LAYER_INTEL_gvk_restore_point", state)
    {}

}

#endif