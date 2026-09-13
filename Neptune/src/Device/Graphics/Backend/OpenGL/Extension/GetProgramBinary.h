/**
* @file GetProgramBinary.h.
* @brief The GetProgramBinary Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IGetProgramBinary = IExtension<class GetProgramBinary, EExtension::GetProgramBinary>;
    
    class GetProgramBinary : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 41;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit GetProgramBinary(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~GetProgramBinary() override = default;
        
    private:
        
        std::vector<GLint> m_Formats;
    };
}

#endif