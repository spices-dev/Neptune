/**
* @file Capabilities.cpp.
* @brief The Capabilities Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Capabilities.h"

namespace Neptune::OpenGL {

    Capabilities::Capabilities(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Capabilities::Create()
    {
        NEPTUNE_PROFILE_ZONE

        GLint major = 0;
        GLint minor = 0;
        
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        
        GLint count = 0;
        
        glGetIntegerv(GL_NUM_EXTENSIONS, &count);
        
        for (GLint i = 0; i < count; ++i)
        {
            const auto* name = glGetStringi(GL_EXTENSIONS, static_cast<GLuint>(i));
            
            if (!name) continue;
            
            m_Extensions.emplace_back(reinterpret_cast<const char*>(name));
        }
    }

}

#endif