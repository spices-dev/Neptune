/**
* @file SeparateShaderObjects.h.
* @brief The SeparateShaderObjects Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using ISeparateShaderObjects = IExtension<class SeparateShaderObjects, EExtension::SeparateShaderObjects>;
    
    class SeparateShaderObjects : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 41;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit SeparateShaderObjects(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~SeparateShaderObjects() override = default;
    };
}

#endif