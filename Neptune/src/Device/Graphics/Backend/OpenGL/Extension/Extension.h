/**
* @file Extension.h.
* @brief The Extension Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/OpenGL/Core.h"

namespace Neptune::OpenGL::Extension {
    
    /**
    * @brief Enum of Extension State.
    */
    enum class EExtensionState : uint8_t
    {
        Core = 0,       // @brief Core.
        Extent,         // @brief Extent.
    };
    
    /**
    * @brief OpenGL::Extension Class.
    * This class defines the OpenGL::Extension behaves.
    */
    class Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Extension(EExtensionState state = EExtensionState::Core) : m_State(state) {}
        
        /**
        * @brief Destructor Function.
        */
        virtual ~Extension() = default;

        /**
        * @brief Get EExtensionState.
        * 
        * @return Returns EExtensionState.
        */
        EExtensionState GetState() const { return m_State; }
        
        /**
        * @brief Add Extension Requirement.
        * 
        * @param[in] name Extension Name.
        * @param[in] value On/Off.
        */
        void AddExtensions(const char* name, bool value = true);
        
        /**
        * @brief Get Extension Requirement.
        * 
        * @return Returns Extension Requirement.
        */
        const std::unordered_map<const char*, bool>& GetExtensions() const { return m_Extensions; }
        
    private:
        
        EExtensionState m_State;                                         // @brief EExtensionState.
        std::unordered_map<const char*, bool> m_Extensions;              // @brief Extensions.
    };
}

#endif