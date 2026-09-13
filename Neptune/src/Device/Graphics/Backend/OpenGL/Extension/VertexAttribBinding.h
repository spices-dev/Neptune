/**
* @file VertexAttribBinding.h.
* @brief The VertexAttribBinding Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IVertexAttribBinding = IExtension<class VertexAttribBinding, EExtension::VertexAttribBinding>;
    
    class VertexAttribBinding : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit VertexAttribBinding(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~VertexAttribBinding() override = default;
        
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
        
        GLint m_MaxBindings;
        GLint m_MaxRelativeOffset;
        GLint m_MaxAttribs;
    };
}

#endif