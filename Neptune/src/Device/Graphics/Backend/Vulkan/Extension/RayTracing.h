/**
* @file RayTracing.h.
* @brief The RayTracing Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IRayTracing = IExtension<class RayTracing, EExtension::RayTracing>;
    
    class RayTracing : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit RayTracing(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~RayTracing() override = default;
    };
}

#endif