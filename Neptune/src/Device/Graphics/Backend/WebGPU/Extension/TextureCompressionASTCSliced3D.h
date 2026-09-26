/**
* @file TextureCompressionASTCSliced3D.h.
* @brief The TextureCompressionASTCSliced3D Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureCompressionASTCSliced3D = IExtension<class TextureCompressionASTCSliced3D, EExtension::TextureCompressionASTCSliced3D>;
    
    class TextureCompressionASTCSliced3D : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureCompressionASTCSliced3D(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureCompressionASTCSliced3D() override = default;
    };
}

#endif