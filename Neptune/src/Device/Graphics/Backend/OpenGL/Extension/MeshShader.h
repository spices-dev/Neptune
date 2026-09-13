/**
* @file MeshShader.h.
* @brief The MeshShader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IMeshShader = IExtension<class MeshShader, EExtension::MeshShader>;
    
    class MeshShader : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit MeshShader(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MeshShader() override = default;
        
        /**
        * @brief Query Extension Properties.
        */
        void QueryProperties() override;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
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