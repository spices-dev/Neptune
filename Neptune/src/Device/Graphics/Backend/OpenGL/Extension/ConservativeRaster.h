/**
* @file ConservativeRaster.h.
* @brief The ConservativeRaster Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IConservativeRaster = IExtension<class ConservativeRaster, EExtension::ConservativeRaster>;
    
    class ConservativeRaster : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ConservativeRaster(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ConservativeRaster() override = default;
        
    private:
        
        GLint m_MaxSubpixelPrecisionBiasBits;
    };
}

#endif