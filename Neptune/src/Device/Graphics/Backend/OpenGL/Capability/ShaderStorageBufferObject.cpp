/**
* @file ShaderStorageBufferObject.cpp.
* @brief The ShaderStorageBufferObject Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderStorageBufferObject.h"

namespace Neptune::OpenGL::Capability {

    ShaderStorageBufferObject::ShaderStorageBufferObject(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_ARB_shader_storage_buffer_object");
        
        glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &m_MaxBinding);
        glGetInteger64v(GL_MAX_SHADER_STORAGE_BLOCK_SIZE, &m_MaxBlockSize);
        glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &m_OffsetAlignment);
        glGetIntegerv(GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, &m_MaxComputeBlocks);
    }

}

#endif