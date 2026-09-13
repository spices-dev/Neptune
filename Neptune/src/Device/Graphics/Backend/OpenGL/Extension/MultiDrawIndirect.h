/**
* @file MultiDrawIndirect.h.
* @brief The MultiDrawIndirect Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IMultiDrawIndirect = IExtension<class MultiDrawIndirect, EExtension::MultiDrawIndirect>;
    
    class MultiDrawIndirect : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 43;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit MultiDrawIndirect(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MultiDrawIndirect() override = default;
    };
}

#endif