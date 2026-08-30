/**
* @file Layer.h.
* @brief The Layer Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Core/Container/KVTuple.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"

namespace Neptune::Vulkan::Layer {
    
    /**
    * @brief Enum of Layer State.
    */
    enum class ELayerState : uint8_t
    {
        Core = 0,       // @brief Core.
        Extent,         // @brief Extent.
    };
    
    /**
    * @brief Vulkan::Layer Class.
    * This class defines the Vulkan::Layer behaves.
    */
    class Layer
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] name Layer Name.
        * @param[in] state ELayerState.
        */
        Layer(const std::string& name, ELayerState state = ELayerState::Extent) : m_State(state), m_InstanceLayer(name) {}
        
        /**
        * @brief Destructor Function.
        */
        virtual ~Layer() = default;

        /**
        * @brief Get ELayerState.
        * 
        * @return Returns ELayerState.
        */
        ELayerState GetState() const { return m_State; }

        /**
        * @brief Add Layer Setting.
        *
        * @param[in] setting VkLayerSettingEXT.
        */
        void AddLayerSetting(const VkLayerSettingEXT& setting);

        /**
        * @brief Get VkInstance Layer Requirement.
        * 
        * @return Returns VkInstance Layer Requirement.
        */
        const std::string& GetInstanceLayer() const { return m_InstanceLayer; }

        /**
        * @brief Build Layer Setting Chain.
        *
        * @param[in,out] settings VkLayerSettingEXT.
        */
        void BuildLayerSettingChain(std::vector<VkLayerSettingEXT>& settings);

    private:
        
        ELayerState m_State;                        // @brief ELayerState.
        std::string m_InstanceLayer;                // @brief VkInstance Layers.
        std::vector<VkLayerSettingEXT> m_Settings;  // @brief VkLayerSettingEXT.
    };
}

#endif