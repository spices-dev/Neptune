/**
* @file MemoryObject.h.
* @brief The MemoryObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IMemoryObject = ICapability<class MemoryObject, ECapability::MemoryObject>;
    
    class MemoryObject : public Capability
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit MemoryObject(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~MemoryObject() override = default;
    };
}

#endif