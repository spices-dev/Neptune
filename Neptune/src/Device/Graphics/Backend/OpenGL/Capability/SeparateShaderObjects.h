/**
* @file SeparateShaderObjects.h.
* @brief The SeparateShaderObjects Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ISeparateShaderObjects = ICapability<class SeparateShaderObjects, ECapability::SeparateShaderObjects>;
    
    class SeparateShaderObjects : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 41;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit SeparateShaderObjects(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~SeparateShaderObjects() override = default;
    };
}

#endif