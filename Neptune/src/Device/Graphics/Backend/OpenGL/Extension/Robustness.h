/**
* @file Robustness.h.
* @brief The Robustness Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IRobustness = IExtension<class Robustness, EExtension::Robustness>;
    
    class Robustness : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 45;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit Robustness(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Robustness() override = default;
        
    private:
        
        GLint m_ResetStrategy;
        GLint m_ContextRobust;
    };
}

#endif