/**
* @file MultiBind.h.
* @brief The MultiBind Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IMultiBind = IExtension<class MultiBind, EExtension::MultiBind>;
    
    class MultiBind : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 44;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit MultiBind(EExtensionState state = EExtensionState::Core);

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