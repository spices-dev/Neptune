/**
* @file CrashDiagnostic.cpp.
* @brief The CrashDiagnostic Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "CrashDiagnostic.h"

namespace Neptune::Vulkan::Layer {

    CrashDiagnostic::CrashDiagnostic(ELayerState state)
        : Layer(state)
    {
        NEPTUNE_PROFILE_ZONE
    }

}

#endif