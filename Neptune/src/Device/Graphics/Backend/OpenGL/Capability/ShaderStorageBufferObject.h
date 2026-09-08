/**
* @file ShaderStorageBufferObject.h.
* @brief The ShaderStorageBufferObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShaderStorageBufferObject = ICapability<class ShaderStorageBufferObject, ECapability::ShaderStorageBufferObject>;
    
    class ShaderStorageBufferObject : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShaderStorageBufferObject(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderStorageBufferObject() override = default;
        
    private:
        
        GLint m_MaxBinding;
        GLint64 m_MaxBlockSize;
        GLint m_OffsetAlignment;
        GLint m_MaxComputeBlocks;
    };
}

#endif