/**
* @file MeshShader.h.
* @brief The MeshShader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IMeshShader = ICapability<class MeshShader, ECapability::MeshShader>;
    
    class MeshShader : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit MeshShader(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MeshShader() override = default;
        
    private:
        
        GLint                 m_MaxMeshOutputVertices;
        GLint                 m_MaxMeshOutputPrimitives;
        GLint                 m_MaxMeshWorkGroupInvocations;
        GLint                 m_MaxTaskWorkGroupInvocations;
        GLint                 m_MaxDrawMeshTasksCount;
        std::array<GLint, 3>  m_MaxMeshWorkGroupSize;
        std::array<GLint, 3>  m_MaxTaskWorkGroupSize;
    };
}

#endif