/**
* @file Capability.cpp.
* @brief The Capability Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Capability.h"

namespace Neptune::OpenGL::Capability {
    
    void Capability::AddExtensions(const char* name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_Extensions.emplace(name, value);
    }
}

#endif