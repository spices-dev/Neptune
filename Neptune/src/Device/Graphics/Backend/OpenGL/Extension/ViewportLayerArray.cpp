/**
* @file ViewportLayerArray.cpp.
* @brief The ViewportLayerArray Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ViewportLayerArray.h"

namespace Neptune::OpenGL::Extension {

    ViewportLayerArray::ViewportLayerArray(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;
        
        AddExtensions("GL_ARB_viewport_layer_array");
    }

}

#endif