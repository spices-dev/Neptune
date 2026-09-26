/**
* @file TextureCompressionBCSliced3D.h.
* @brief The TextureCompressionBCSliced3D Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ITextureCompressionBCSliced3D = IExtension<class TextureCompressionBCSliced3D, EExtension::TextureCompressionBCSliced3D>;
    
    class TextureCompressionBCSliced3D : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit TextureCompressionBCSliced3D(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~TextureCompressionBCSliced3D() override = default;
    };
}

#endif