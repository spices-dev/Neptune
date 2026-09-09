/**
* @file FragmentShaderBarycentric.h.
* @brief The FragmentShaderBarycentric Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IFragmentShaderBarycentric = ICapability<class FragmentShaderBarycentric, ECapability::FragmentShaderBarycentric>;
    
    class FragmentShaderBarycentric : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit FragmentShaderBarycentric(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~FragmentShaderBarycentric() override = default;
    };
}

#endif