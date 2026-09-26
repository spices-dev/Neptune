/**
* @file Snorm16TextureFormats.h.
* @brief The Snorm16TextureFormats Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using ISnorm16TextureFormats = IExtension<class Snorm16TextureFormats, EExtension::Snorm16TextureFormats>;
    
    class Snorm16TextureFormats : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Snorm16TextureFormats(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Snorm16TextureFormats() override = default;
    };
}

#endif