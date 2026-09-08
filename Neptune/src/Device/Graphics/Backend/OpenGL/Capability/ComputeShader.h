/**
* @file ComputeShader.h.
* @brief The ComputeShader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IComputeShader = ICapability<class ComputeShader, ECapability::ComputeShader>;
    
    class ComputeShader : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit ComputeShader(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ComputeShader() override = default;
        
    private:
        
        std::array<GLint, 3> m_MaxWorkGroupCount;
        std::array<GLint, 3> m_MaxWorkGroupSize;
        GLint m_MaxWorkGroupInvocations;
        GLint m_MaxSharedMemorySize;
    };
}

#endif