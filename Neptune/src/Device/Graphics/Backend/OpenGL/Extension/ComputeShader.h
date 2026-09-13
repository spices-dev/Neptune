/**
* @file ComputeShader.h.
* @brief The ComputeShader Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IComputeShader = IExtension<class ComputeShader, EExtension::ComputeShader>;
    
    class ComputeShader : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit ComputeShader(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~ComputeShader() override = default;
        
        /**
        * @brief Query Extension Properties.
        */
        void QueryProperties() override;
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
    private:
        
        std::array<GLint, 3> m_MaxWorkGroupCount;
        std::array<GLint, 3> m_MaxWorkGroupSize;
        GLint m_MaxWorkGroupInvocations;
        GLint m_MaxSharedMemorySize;
    };
}

#endif