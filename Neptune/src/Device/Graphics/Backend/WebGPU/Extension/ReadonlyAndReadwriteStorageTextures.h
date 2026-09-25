/**
* @file ReadonlyAndReadwriteStorageTextures.h.
* @brief The ReadonlyAndReadwriteStorageTextures Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IReadonlyAndReadwriteStorageTextures = IExtension<class ReadonlyAndReadwriteStorageTextures, EExtension::ReadonlyAndReadwriteStorageTextures>;
    
    class ReadonlyAndReadwriteStorageTextures : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ReadonlyAndReadwriteStorageTextures(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ReadonlyAndReadwriteStorageTextures() override = default;
    };
}

#endif