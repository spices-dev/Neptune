/**
* @file ShadingRateImage.h.
* @brief The ShadingRateImage Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IShadingRateImage = IExtension<class ShadingRateImage, EExtension::ShadingRateImage>;
    
    class ShadingRateImage : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ShadingRateImage(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShadingRateImage() override = default;
        
    private:
        
        GLint m_TexelWidth;
        GLint m_TexelHeight;
        GLint m_PaletteSize;
    };
}

#endif