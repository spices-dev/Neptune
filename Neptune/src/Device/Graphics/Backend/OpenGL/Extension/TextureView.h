/**
* @file TextureView.h.
* @brief The TextureView Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ITextureView = IExtension<class TextureView, EExtension::TextureView>;
    
    class TextureView : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit TextureView(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureView() override = default;
    };
}

#endif