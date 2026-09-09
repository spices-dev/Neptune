/**
* @file ShaderSubGroup.cpp.
* @brief The ShaderSubGroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "ShaderSubGroup.h"

namespace Neptune::OpenGL::Capability {

    ShaderSubGroup::ShaderSubGroup(ECapabilityState state)
        : Capability(state)
    {
        NEPTUNE_PROFILE_ZONE

        if constexpr (IsCoreCapability<decltype(*this)>) return;

        AddExtensions("GL_NV_shader_subgroup");
        
        glGetIntegerv(GL_SUBGROUP_SIZE_KHR, &m_SubgroupSize);
        glGetIntegerv(GL_SUBGROUP_SUPPORTED_STAGES_KHR, &m_SupportedStages);
        glGetIntegerv(GL_SUBGROUPSUPPORTED_FEATURES_KHR_, &m_SupportedFeatures);
    }

}

#endif