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
        * @brief Set ApiVersion.
        * 
        * @param[in] version ApiVersion.
        */
        static void SetApiVersion(uint32_t version);
        
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
        void AddExtensions(const std::string& name, bool value = true);
        
        /**
        * @brief Get Extension Requirement.
        * 
        * @return Returns Extension Requirement.
        */
        const std::unordered_map<std::string, bool>& GetExtensions() const { return m_Extensions; }
        
        /**
        * @brief Query Extension Properties.
        */
        virtual void QueryProperties() {}
        
        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsPropertiesSatisfied() { return true; }
        
        /**
        * @brief Is IsCoreExtension.
        * 
        * @tparam T IsExtension.
        */
        template<typename T>
        requires IsBase<Extension, Decay<T>>
        bool IsCoreExtension() const;
        
    private:
        
        /**
        * @brief Get ApiVersion.
        * 
        * @return Returns ApiVersion.
        */
        uint32_t GetApiVersion() const;
        
    private:
        
        EExtensionState m_State;                                         // @brief EExtensionState.
        std::unordered_map<std::string, bool> m_Extensions{};            // @brief Extensions.
    };

    template <typename T> 
    requires IsBase<Extension, Decay<T>>
    bool Extension::IsCoreExtension() const
    {
        NEPTUNE_PROFILE_ZONE
        
        if constexpr (!requires { Decay<T>::CoreVersion; })
        {
            return false;
        }
        else
        {
            return GetApiVersion() >= Decay<T>::CoreVersion;
        }
    }
}

#endif