/**
* @file Capability.h.
* @brief The Capability Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/OpenGL/Core.h"

namespace Neptune::OpenGL::Capability {
    
    /**
    * @brief Enum of Capability State.
    */
    enum class ECapabilityState : uint8_t
    {
        Core = 0,       // @brief Core.
        Extent,         // @brief Extent.
    };
    
    /**
    * @brief OpenGL::Extension Class.
    * This class defines the OpenGL::Extension behaves.
    */
    class Capability
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state ECapabilityState.
        */
        explicit Capability(ECapabilityState state = ECapabilityState::Core) : m_State(state) {}
        
        /**
        * @brief Destructor Function.
        */
        virtual ~Capability() = default;

        /**
        * @brief Get ECapabilityState.
        * 
        * @return Returns ECapabilityState.
        */
        ECapabilityState GetState() const { return m_State; }
        
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
        
        ECapabilityState m_State;                                        // @brief ECapabilityState.
        std::unordered_map<const char*, bool> m_Extensions;              // @brief Extensions.
    };
}

#endif