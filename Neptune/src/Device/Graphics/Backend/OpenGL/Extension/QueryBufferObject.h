/**
* @file QueryBufferObject.h.
* @brief The QueryBufferObject Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IQueryBufferObject = IExtension<class QueryBufferObject, EExtension::QueryBufferObject>;
    
    class QueryBufferObject : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 44;
    
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit QueryBufferObject(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~QueryBufferObject() override = default;
    };
}

#endif