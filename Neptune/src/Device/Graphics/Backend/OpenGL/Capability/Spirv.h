/**
* @file Spirv.h.
* @brief The Spirv Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using ISpirv = ICapability<class Spirv, ECapability::Spirv>;
    
    class Spirv : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 46;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit Spirv(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~Spirv() override = default;
        
    private:
        
        std::unordered_set<const char*> m_SpirVExtensions;
    };
}

#endif