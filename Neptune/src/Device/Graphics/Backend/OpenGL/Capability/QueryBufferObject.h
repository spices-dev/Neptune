/**
* @file QueryBufferObject.h.
* @brief The QueryBufferObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IQueryBufferObject = ICapability<class QueryBufferObject, ECapability::QueryBufferObject>;
    
    class QueryBufferObject : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 44;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit QueryBufferObject(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~QueryBufferObject() override = default;
    };
}

#endif