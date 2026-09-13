/**
* @file BufferStorage.h.
* @brief The BufferStorage Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::OpenGL::Extension {

    using IBufferStorage = IExtension<class BufferStorage, EExtension::BufferStorage>;
    
    class BufferStorage : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = 44;
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit BufferStorage(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~BufferStorage() override = default;
        
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
        
        GLint m_MinMapAlignment;
    };
}

#endif