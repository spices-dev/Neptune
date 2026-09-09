/**
* @file ShadingRateImage.h.
* @brief The ShadingRateImage Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShadingRateImage = ICapability<class ShadingRateImage, ECapability::ShadingRateImage>;
    
    class ShadingRateImage : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShadingRateImage(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShadingRateImage() override = default;
    };
}

#endif