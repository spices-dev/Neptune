/**
* @file FragmentShaderBarycentric.h.
* @brief The FragmentShaderBarycentric Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IFragmentShaderBarycentric = IExtension<class FragmentShaderBarycentric, EExtension::FragmentShaderBarycentric>;
    
    class FragmentShaderBarycentric : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit FragmentShaderBarycentric(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~FragmentShaderBarycentric() override = default;
    };
}

#endif