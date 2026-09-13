/**
* @file Extension.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Extension.h"

namespace Neptune::OpenGL::Extension {
    
    void Extension::AddExtensions(const char* name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_Extensions.emplace(name, value);
    }
}

#endif