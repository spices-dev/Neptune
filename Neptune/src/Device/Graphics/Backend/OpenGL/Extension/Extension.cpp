/**
* @file Extension.cpp.
* @brief The Extension Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Extension.h"

namespace Neptune::OpenGL::Extension {
    
    namespace {
        
        uint32_t s_ApiVersion = OPENGL_DEV_VERSION;       // @brief Api Version.
    }
    
    void Extension::SetApiVersion(uint32_t version)
    {
        NEPTUNE_PROFILE_ZONE
        
        s_ApiVersion = version;
    }

    void Extension::AddExtensions(const char* name, bool value)
    {
        NEPTUNE_PROFILE_ZONE

        m_Extensions.emplace(name, value);
    }

    uint32_t Extension::GetApiVersion() const
    {
        NEPTUNE_PROFILE_ZONE
        
        return s_ApiVersion;
    }
}

#endif