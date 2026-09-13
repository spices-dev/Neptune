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

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_sparse_texture");
    }

    void SparseTexture::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_MAX_SPARSE_TEXTURE_SIZE_ARB, &m_MaxSize);
        glGetIntegerv(GL_MAX_SPARSE_3D_TEXTURE_SIZE_ARB, &m_Max3DSize);
        glGetIntegerv(GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS, &m_MaxArrayLayers);
    }
    
    bool SparseTexture::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "SparseTexture [ maxSize ] : " << m_MaxSize;
        NEPTUNE_LOG_CORE(I) << "SparseTexture [ max3DSize ] : " << m_Max3DSize;
        NEPTUNE_LOG_CORE(I) << "SparseTexture [ maxArrayLayers ] : " << m_MaxArrayLayers;

        return true;
    }
    
}

#endif