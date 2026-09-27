/**
* @file TextureCompressionUnaligned.h.
* @brief The TextureCompressionUnaligned Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureCompressionUnaligned = IExtension<class TextureCompressionUnaligned, EExtension::TextureCompressionUnaligned>;
    
    class TextureCompressionUnaligned : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureCompressionUnaligned(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureCompressionUnaligned() override = default;
    };
}

#endif