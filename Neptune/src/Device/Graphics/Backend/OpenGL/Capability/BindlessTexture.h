/**
* @file BindlessTexture.h.
* @brief The BindlessTexture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

typedef GLuint64  (APIENTRYP PFN_GetTextureHandleARB)               (GLuint texture);
typedef GLuint64  (APIENTRYP PFN_GetTextureSamplerHandleARB)        (GLuint texture, GLuint sampler);
typedef void      (APIENTRYP PFN_glMakeTextureHandleResidentARB)    (GLuint64 handle);
typedef void      (APIENTRYP PFN_glMakeTextureHandleNonResidentARB) (GLuint64 handle);
typedef GLboolean (APIENTRYP PFN_glIsTextureHandleResidentARB)      (GLuint64 handle);
typedef void      (APIENTRYP PFN_glUniformHandleui64ARB)            (GLint location, GLuint64 value);

namespace Neptune::OpenGL::Capability {

    using IBindlessTexture = ICapability<class BindlessTexture, ECapability::BindlessTexture>;
    
    class BindlessTexture : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit BindlessTexture(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~BindlessTexture() override = default;
        
    private:
        
        PFN_GetTextureHandleARB               glGetTextureHandleARB             = reinterpret_cast<PFN_GetTextureHandleARB>               (std::invoke(loader, "glGetTextureHandleARB"));
        PFN_GetTextureSamplerHandleARB        glGetTextureSamplerHandleARB      = reinterpret_cast<PFN_GetTextureSamplerHandleARB>        (std::invoke(loader, "glGetTextureSamplerHandleARB"));
        PFN_glMakeTextureHandleResidentARB    glMakeTextureHandleResidentARB    = reinterpret_cast<PFN_glMakeTextureHandleResidentARB>    (std::invoke(loader, "glMakeTextureHandleResidentARB"));
        PFN_glMakeTextureHandleNonResidentARB glMakeTextureHandleNonResidentARB = reinterpret_cast<PFN_glMakeTextureHandleNonResidentARB> (std::invoke(loader, "glMakeTextureHandleNonResidentARB"));
        PFN_glIsTextureHandleResidentARB      glIsTextureHandleResidentARB      = reinterpret_cast<PFN_glIsTextureHandleResidentARB>      (std::invoke(loader, "glIsTextureHandleResidentARB"));
        PFN_glUniformHandleui64ARB            glUniformHandleui64ARB            = reinterpret_cast<PFN_glUniformHandleui64ARB>            (std::invoke(loader, "glUniformHandleui64ARB"));
    };
}

#endif