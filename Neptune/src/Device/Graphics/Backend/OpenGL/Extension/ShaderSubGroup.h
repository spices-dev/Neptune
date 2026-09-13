/**
* @file ShaderSubGroup.h.
* @brief The ShaderSubGroup Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IShaderSubGroup = IExtension<class ShaderSubGroup, EExtension::ShaderSubGroup>;
    
    class ShaderSubGroup : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ShaderSubGroup(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ShaderSubGroup() override = default;
        
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
        
        GLint m_SubgroupSize;
        GLint m_SupportedStages;
        GLint m_SupportedFeatures;
    };
}

#endif