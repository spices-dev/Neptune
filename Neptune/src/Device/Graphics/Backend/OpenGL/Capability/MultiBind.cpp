/**
* @file MultiBind.cpp.
* @brief The MultiBind Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MultiBind.h"

namespace Neptune::OpenGL::Capability {

    MultiBind::MultiBind(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_multi_bind");
        
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &m_MaxTextureUnits);
        glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &m_MaxUniformBinding);
    }

}

#endif