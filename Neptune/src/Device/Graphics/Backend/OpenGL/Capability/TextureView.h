/**
* @file TextureView.h.
* @brief The TextureView Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ITextureView = ICapability<class TextureView, ECapability::TextureView>;
    
    class TextureView : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit TextureView(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureView() override = default;
    };
}

#endif