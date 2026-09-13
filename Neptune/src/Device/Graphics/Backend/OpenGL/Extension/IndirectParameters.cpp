/**
* @file IndirectParameters.cpp.
* @brief The IndirectParameters Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "IndirectParameters.h"

namespace Neptune::OpenGL::Extension {

    IndirectParameters::IndirectParameters(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_ARB_indirect_parameters");
    }

}

#endif