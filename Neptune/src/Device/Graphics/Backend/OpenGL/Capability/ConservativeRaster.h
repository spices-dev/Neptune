/**
* @file ConservativeRaster.h.
* @brief The ConservativeRaster Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IConservativeRaster = ICapability<class ConservativeRaster, ECapability::ConservativeRaster>;
    
    class ConservativeRaster : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ConservativeRaster(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ConservativeRaster() override = default;
        
    private:
        
        GLint m_MaxSubpixelPrecisionBiasBits;
    };
}

#endif