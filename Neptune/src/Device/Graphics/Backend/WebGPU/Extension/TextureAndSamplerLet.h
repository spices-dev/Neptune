/**
* @file TextureAndSamplerLet.h.
* @brief The TextureAndSamplerLet Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureAndSamplerLet = IExtension<class TextureAndSamplerLet, EExtension::TextureAndSamplerLet>;
    
    class TextureAndSamplerLet : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureAndSamplerLet(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureAndSamplerLet() override = default;
    };
}

#endif