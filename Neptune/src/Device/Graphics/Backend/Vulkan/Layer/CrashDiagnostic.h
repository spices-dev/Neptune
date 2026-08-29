/**
* @file CrashDiagnostic.h.
* @brief The CrashDiagnostic Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Layer {

    using ICrashDiagnostic = ILayer<class CrashDiagnostic, ELayer::CrashDiagnostic>;

    class CrashDiagnostic : public Layer
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ELayerState.
        */
        explicit CrashDiagnostic(ELayerState state = ELayerState::Extent);

        /**
        * @brief Destructor Function.
        */
        ~CrashDiagnostic() override = default;
    };
}

#endif