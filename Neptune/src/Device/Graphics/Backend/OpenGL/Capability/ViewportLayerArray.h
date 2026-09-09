/**
* @file ViewportLayerArray.h.
* @brief The ViewportLayerArray Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IViewportLayerArray = ICapability<class ViewportLayerArray, ECapability::ViewportLayerArray>;
    
    class ViewportLayerArray : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ViewportLayerArray(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ViewportLayerArray() override = default;
    };
}

#endif