/**
* @file TextureFormatsTier2.h.
* @brief The TextureFormatsTier2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureFormatsTier2 = IExtension<class TextureFormatsTier2, EExtension::TextureFormatsTier2>;
    
    class TextureFormatsTier2 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureFormatsTier2(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureFormatsTier2() override = default;
    };
}

#endif