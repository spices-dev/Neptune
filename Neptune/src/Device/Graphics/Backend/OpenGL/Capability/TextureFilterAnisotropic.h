/**
* @file TextureFilterAnisotropic.h.
* @brief The TextureFilterAnisotropic Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ITextureFilterAnisotropic = ICapability<class TextureFilterAnisotropic, ECapability::TextureFilterAnisotropic>;
    
    class TextureFilterAnisotropic : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit TextureFilterAnisotropic(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureFilterAnisotropic() override = default;
    };
}

#endif