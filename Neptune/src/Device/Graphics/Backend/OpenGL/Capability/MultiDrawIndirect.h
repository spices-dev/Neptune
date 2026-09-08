/**
* @file MultiDrawIndirect.h.
* @brief The MultiDrawIndirect Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IMultiDrawIndirect = ICapability<class MultiDrawIndirect, ECapability::MultiDrawIndirect>;
    
    class MultiDrawIndirect : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit MultiDrawIndirect(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MultiDrawIndirect() override = default;
    };
}

#endif