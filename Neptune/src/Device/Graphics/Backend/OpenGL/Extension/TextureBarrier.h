/**
* @file TextureBarrier.h.
* @brief The TextureBarrier Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ITextureBarrier = IExtension<class TextureBarrier, EExtension::TextureBarrier>;
    
    class TextureBarrier : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit TextureBarrier(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureBarrier() override = default;
    };
}

#endif