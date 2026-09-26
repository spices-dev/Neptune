/**
* @file TextureFormatsTier1.h.
* @brief The TextureFormatsTier1 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureFormatsTier1 = IExtension<class TextureFormatsTier1, EExtension::TextureFormatsTier1>;
    
    class TextureFormatsTier1 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureFormatsTier1(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureFormatsTier1() override = default;
    };
}

#endif