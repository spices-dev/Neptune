/**
* @file ShaderSubGroup.cpp.
* @brief The ShaderSubGroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderSubGroup.h"

namespace Neptune::OpenGL::Extension {

    ShaderSubGroup::ShaderSubGroup(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddExtensions("GL_NV_shader_subgroup");
    }
    
    void ShaderSubGroup::QueryProperties()
    {
        NEPTUNE_PROFILE_ZONE
        
        glGetIntegerv(GL_SUBGROUP_SIZE_KHR, &m_SubgroupSize);
        glGetIntegerv(GL_SUBGROUP_SUPPORTED_STAGES_KHR, &m_SupportedStages);
        glGetIntegerv(GL_SUBGROUP_SUPPORTED_FEATURES_KHR, &m_SupportedFeatures);
    }
    
    bool ShaderSubGroup::IsPropertiesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "ShaderSubGroup [ subgroupSize ] : " << m_SubgroupSize;
        NEPTUNE_LOG_CORE(I) << "ShaderSubGroup [ supportedStages ] : " << m_SupportedStages;
        NEPTUNE_LOG_CORE(I) << "ShaderSubGroup [ supportedFeatures ] : " << m_SupportedFeatures;

        return true;
    }

}

#endif