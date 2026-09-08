/**
* @file SparseTexture.cpp.
* @brief The SparseTexture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "SparseTexture.h"

namespace Neptune::OpenGL::Capability {

    SparseTexture::SparseTexture(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_sparse_texture");
        
        // TODO
    }

}

#endif