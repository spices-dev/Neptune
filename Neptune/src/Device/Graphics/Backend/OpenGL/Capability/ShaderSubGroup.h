/**
* @file ShaderSubGroup.h.
* @brief The ShaderSubGroup Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IShaderSubGroup = ICapability<class ShaderSubGroup, ECapability::ShaderSubGroup>;
    
    class ShaderSubGroup : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ShaderSubGroup(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderSubGroup() override = default;
        
    private:
        
        GLint m_SubgroupSize;
        GLint m_SupportedStages;
        GLint m_SupportedFeatures;
    };
}

#endif