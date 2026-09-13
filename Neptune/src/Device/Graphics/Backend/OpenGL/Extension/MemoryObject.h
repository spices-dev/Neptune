/**
* @file MemoryObject.h.
* @brief The MemoryObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IMemoryObject = IExtension<class MemoryObject, EExtension::MemoryObject>;
    
    class MemoryObject : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit MemoryObject(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MemoryObject() override = default;
    };
}

#endif