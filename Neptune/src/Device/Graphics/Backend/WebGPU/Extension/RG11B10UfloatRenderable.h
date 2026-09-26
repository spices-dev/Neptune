/**
* @file RG11B10UfloatRenderable.h.
* @brief The RG11B10UfloatRenderable Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::WebGPU::Extension {

    using IRG11B10UfloatRenderable = IExtension<class RG11B10UfloatRenderable, EExtension::RG11B10UfloatRenderable>;
    
    class RG11B10UfloatRenderable : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit RG11B10UfloatRenderable(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~RG11B10UfloatRenderable() override = default;
    };
}

#endif