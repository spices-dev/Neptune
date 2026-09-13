/**
* @file Spirv.cpp.
* @brief The Spirv Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Spirv.h"

namespace Neptune::OpenGL::Extension {

    Spirv::Spirv(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_ARB_gl_spirv");
        
        GLint count;
        
        glGetIntegerv(GL_NUM_SPIR_V_EXTENSIONS, &count);
        
        m_SpirVExtensions.reserve(count);
        
        for (GLint i = 0; i < count; ++i)
        {
            const auto* name = glGetStringi(GL_SPIR_V_EXTENSIONS, i);
            
            if (!name) continue;
            
            m_SpirVExtensions.emplace(reinterpret_cast<const char*>(name));
        }
    }

}

#endif