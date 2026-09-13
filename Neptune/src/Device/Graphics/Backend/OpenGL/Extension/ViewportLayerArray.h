/**
* @file ViewportLayerArray.h.
* @brief The ViewportLayerArray Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IViewportLayerArray = IExtension<class ViewportLayerArray, EExtension::ViewportLayerArray>;
    
    class ViewportLayerArray : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ViewportLayerArray(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ViewportLayerArray() override = default;
    };
}

#endif