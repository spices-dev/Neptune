/**
* @file TextureCompressionASTC.h.
* @brief The TextureCompressionASTC Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureCompressionASTC = IExtension<class TextureCompressionASTC, EExtension::TextureCompressionASTC>;
    
    class TextureCompressionASTC : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureCompressionASTC(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureCompressionASTC() override = default;
    };
}

#endif