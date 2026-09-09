/**
* @file VertexAttribBinding.h.
* @brief The VertexAttribBinding Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IVertexAttribBinding = ICapability<class VertexAttribBinding, ECapability::VertexAttribBinding>;
    
    class VertexAttribBinding : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit VertexAttribBinding(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~VertexAttribBinding() override = default;
        
    private:
        
        GLint m_MaxBindings;
        GLint m_MaxRelativeOffset;
        GLint m_MaxAttribs;
    };
}

#endif