/**
* @file ShaderGroupVote.cpp.
* @brief The ShaderGroupVote Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderGroupVote.h"

namespace Neptune::OpenGL::Extension {

    ShaderGroupVote::ShaderGroupVote(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_shader_group_vote");
    }

}

#endif