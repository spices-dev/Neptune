/**
* @file Unorm16TextureFormats.h.
* @brief The Unorm16TextureFormats Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IUnorm16TextureFormats = IExtension<class Unorm16TextureFormats, EExtension::Unorm16TextureFormats>;
    
    class Unorm16TextureFormats : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Unorm16TextureFormats(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Unorm16TextureFormats() override = default;
    };
}

#endif