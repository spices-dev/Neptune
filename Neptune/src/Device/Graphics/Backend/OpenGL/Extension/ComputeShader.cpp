/**
* @file ComputeShader.cpp.
* @brief The ComputeShader Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ComputeShader.h"

namespace Neptune::OpenGL::Extension {

    ComputeShader::ComputeShader(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_ARB_compute_shader");
    }
    
    void ComputeShader::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        for (GLuint i = 0; i < 3; ++i)
        {
            glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, i, &m_MaxWorkGroupCount[i]);
            
            glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, i, &m_MaxWorkGroupSize[i]);
        }
        
        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &m_MaxWorkGroupInvocations);
        
        glGetIntegerv(GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, &m_MaxSharedMemorySize);
    }
    
    bool ComputeShader::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "ComputeShader [ maxWorkGroupCount ] : " << m_MaxWorkGroupCount[0] << ", " << m_MaxWorkGroupCount[1] << ", " << m_MaxWorkGroupCount[2];
        NEPTUNE_LOG_CORE(I) << "ComputeShader [ maxWorkGroupSize ] : " << m_MaxWorkGroupSize[0] << ", " << m_MaxWorkGroupSize[1] << ", " << m_MaxWorkGroupSize[2];
        NEPTUNE_LOG_CORE(I) << "ComputeShader [ maxWorkGroupInvocations ] : " << m_MaxWorkGroupInvocations;
        NEPTUNE_LOG_CORE(I) << "ComputeShader [ maxSharedMemorySize ] : " << m_MaxSharedMemorySize;

        return true;
    }

}

#endif