/**
* @file TextureComponentSwizzle.h.
* @brief The TextureComponentSwizzle Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureComponentSwizzle = IExtension<class TextureComponentSwizzle, EExtension::TextureComponentSwizzle>;
    
    class TextureComponentSwizzle : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureComponentSwizzle(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureComponentSwizzle() override = default;
    };
}

#endif