/**
* @file TextureCompressionETC2.h.
* @brief The TextureCompressionETC2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureCompressionETC2 = IExtension<class TextureCompressionETC2, EExtension::TextureCompressionETC2>;
    
    class TextureCompressionETC2 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureCompressionETC2(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureCompressionETC2() override = default;
    };
}

#endif