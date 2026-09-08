/**
* @file TextureBarrier.h.
* @brief The TextureBarrier Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ITextureBarrier = ICapability<class TextureBarrier, ECapability::TextureBarrier>;
    
    class TextureBarrier : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit TextureBarrier(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~TextureBarrier() override = default;
    };
}

#endif