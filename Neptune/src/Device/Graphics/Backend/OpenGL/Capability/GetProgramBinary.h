/**
* @file GetProgramBinary.h.
* @brief The GetProgramBinary Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IGetProgramBinary = ICapability<class GetProgramBinary, ECapability::GetProgramBinary>;
    
    class GetProgramBinary : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 41;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit GetProgramBinary(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~GetProgramBinary() override = default;
    };
}

#endif