/**
* @file MeshShader.cpp.
* @brief The MeshShader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "MeshShader.h"

namespace Neptune::OpenGL::Extension {

    MeshShader::MeshShader(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_NV_mesh_shader");
        
        glGetIntegerv(GL_MAX_MESH_OUTPUT_VERTICES_NV, &m_MaxMeshOutputVertices);
        glGetIntegerv(GL_MAX_MESH_OUTPUT_PRIMITIVES_NV, &m_MaxMeshOutputPrimitives);
        glGetIntegerv(GL_MAX_MESH_WORK_GROUP_INVOCATIONS_NV, &m_MaxMeshWorkGroupInvocations);
        glGetIntegerv(GL_MAX_TASK_WORK_GROUP_INVOCATIONS_NV, &m_MaxTaskWorkGroupInvocations);
        glGetIntegerv(GL_MAX_DRAW_MESH_TASKS_COUNT_NV, &m_MaxDrawMeshTasksCount);
        
        for (GLuint i = 0; i < 3; ++i)
        {
            glGetIntegeri_v(GL_MAX_MESH_WORK_GROUP_SIZE_NV, i, &m_MaxMeshWorkGroupSize[i]);
            glGetIntegeri_v(GL_MAX_TASK_WORK_GROUP_SIZE_NV, i, &m_MaxTaskWorkGroupSize[i]);
        }
    }

}

#endif