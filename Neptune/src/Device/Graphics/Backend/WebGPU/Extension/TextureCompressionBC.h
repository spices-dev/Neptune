/**
* @file TextureCompressionBC.h.
* @brief The TextureCompressionBC Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureCompressionBC = IExtension<class TextureCompressionBC, EExtension::TextureCompressionBC>;
    
    class TextureCompressionBC : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureCompressionBC(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureCompressionBC() override = default;
    };
}

#endif