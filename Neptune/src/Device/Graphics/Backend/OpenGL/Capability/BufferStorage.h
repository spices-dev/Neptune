/**
* @file BufferStorage.h.
* @brief The BufferStorage Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Capability {

    using IBufferStorage = ICapability<class BufferStorage, ECapability::BufferStorage>;
    
    class BufferStorage : public Capability
    {
    public:
        
        static constexpr uint32_t CoreVersion = 44;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state ECapabilityState.
        */
        explicit BufferStorage(ECapabilityState state = ECapabilityState::Core);

        /**
        * @brief Destructor Function.
        */
        ~BufferStorage() override = default;
        
    private:
        
        GLint m_MinMapAlignment;
    };
}

#endif