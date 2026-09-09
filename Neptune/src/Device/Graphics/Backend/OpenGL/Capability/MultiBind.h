/**
* @file MultiBind.h.
* @brief The MultiBind Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IMultiBind = ICapability<class MultiBind, ECapability::MultiBind>;
    
    class MultiBind : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 44;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit MultiBind(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MultiBind() override = default;
        
    private:
        
        GLint m_MaxTextureUnits;
        GLint m_MaxUniformBinding;
    };
}

#endif