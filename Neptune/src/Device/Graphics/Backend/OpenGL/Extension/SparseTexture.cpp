/**
* @file SparseTexture.cpp.
* @brief The SparseTexture Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "SparseTexture.h"

namespace Neptune::OpenGL::Extension {

    SparseTexture::SparseTexture(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_ARB_sparse_texture");
        
        glGetIntegerv(GL_MAX_SPARSE_TEXTURE_SIZE_ARB, &m_MaxSize);
        glGetIntegerv(GL_MAX_SPARSE_3D_TEXTURE_SIZE_ARB, &m_Max3DSize);
        glGetIntegerv(GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS, &m_MaxArrayLayers);
    }

}

#endif