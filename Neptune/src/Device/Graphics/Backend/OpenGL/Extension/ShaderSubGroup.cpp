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

        if constexpr (IsCoreExtension<decltype(*this)>) return;

        AddExtensions("GL_NV_shader_subgroup");
        
        glGetIntegerv(GL_SUBGROUP_SIZE_KHR, &m_SubgroupSize);
        glGetIntegerv(GL_SUBGROUP_SUPPORTED_STAGES_KHR, &m_SupportedStages);
        glGetIntegerv(GL_SUBGROUP_SUPPORTED_FEATURES_KHR, &m_SupportedFeatures);
    }

}

#endif