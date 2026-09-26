/**
* @file Extension.h.
* @brief The Extension Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/WebGPU/Core.h"

namespace Neptune::WebGPU::Extension {
    
    /**
    * @brief Enum of Extension State.
    */
    enum class EExtensionState : uint8_t
    {
        Core = 0,       // @brief Core.
        Extent,         // @brief Extent.
    };
    
    /**
    * @brief WebGPU::Extension Class.
    * This class defines the WebGPU::Extension behaves.
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
        * @brief Add Instance Feature Requirement.
        * 
        * @param[in] name WGPUInstanceFeatureName.
        * @param[in] value On/Off.
        */
        void AddInstanceFeatures(const WGPUInstanceFeatureName name, bool value = true);
        
        /**
        * @brief Add WGSLFeature Requirement.
        * 
        * @param[in] name WGPUWGSLLanguageFeatureName.
        * @param[in] value On/Off.
        */
        void AddWGSLFeatures(const WGPUWGSLLanguageFeatureName name, bool value = true);
        
        /**
        * @brief Add Adapter Feature Requirement.
        * 
        * @param[in] name WGPUFeatureName.
        * @param[in] value On/Off.
        */
        void AddAdapterFeatures(const WGPUFeatureName name, bool value = true);
        
        /**
        * @brief Get Instance Feature Requirement.
        * 
        * @return Returns Instance Feature Requirement.
        */
        const std::unordered_map<WGPUInstanceFeatureName, bool>& GetInstanceFeatures() const { return m_InstanceFeatures; }
        
        /**
        * @brief Get WGSLFeature Requirement.
        * 
        * @return Returns WGSLFeature Requirement.
        */
        const std::unordered_map<WGPUWGSLLanguageFeatureName, bool>& GetWGSLFeatures() const { return m_WGSLFeatures; }
        
        /**
        * @brief Get WGPUFeatureName Requirement.
        * 
        * @return Returns WGPUFeatureName Requirement.
        */
        const std::unordered_map<WGPUFeatureName, bool>& GetAdapterFeatures() const { return m_AdapterFeatures; }
        
        /**
        * @brief Is Instance Limits satisfied.
        * 
        * @return Returns true if satisfied.
        */
        virtual bool IsInstanceLimitsSatisfied(WGPUInstanceLimits limits) const { return true; }
        
    private:
        
        EExtensionState                                       m_State;                    // @brief EExtensionState.
        std::unordered_map<WGPUInstanceFeatureName, bool>     m_InstanceFeatures{};       // @brief Instance Features.
        std::unordered_map<WGPUWGSLLanguageFeatureName, bool> m_WGSLFeatures{};           // @brief WGPUWGSLLanguageFeatureName.
        std::unordered_map<WGPUFeatureName, bool>             m_AdapterFeatures{};        // @brief WGPUFeatureName.
    };
}

#endif