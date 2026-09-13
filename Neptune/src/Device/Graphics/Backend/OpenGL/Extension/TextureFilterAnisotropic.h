/**
* @file TextureFilterAnisotropic.h.
* @brief The TextureFilterAnisotropic Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ITextureFilterAnisotropic = IExtension<class TextureFilterAnisotropic, EExtension::TextureFilterAnisotropic>;
    
    class TextureFilterAnisotropic : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit TextureFilterAnisotropic(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureFilterAnisotropic() override = default;
        
    private:
        
        GLfloat m_MaxAnisotropy;
    };
}

#endif