/**
* @file LayerSettingSet.h.
* @brief The LayerSettingSet Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"
#include "Unit.h"

#include <vulkan/layer/vk_layer_settings.hpp>

namespace Neptune::Vulkan::Unit {

    /**
    * @brief Vulkan::Unit::LayerSettingSet Class.
    * This class defines the Vulkan::Unit::LayerSettingSet behaves.
    */
    class LayerSettingSet : public Unit<VkuLayerSettingSet, void, void>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        LayerSettingSet() = default;

        /**
        * @brief Destructor Function.
        */
        ~LayerSettingSet() override;
        
        /**
        * @brief Create LayerSettingSet.
        *
        * @param[in] name LayerName.
        * @param[in] info VkLayerSettingsCreateInfoEXT.
        * 
        * @return Returns VkResult.
        */
        VkResult CreateLayerSettingSet(const char* name, const VkLayerSettingsCreateInfoEXT* info);
        
        /**
        * @brief Get Layer Setting Value.
        *
        * @param[in] name SettingName.
        * @param[out] v Out Value.
        * @param[out] defaultV default Value.
        * 
        * @return Returns VkResult.
        */
        template<typename T>
        VkResult GetValue(const std::string& name, T& v, const T& defaultV);
        
        /**
        * @brief Get Layer Setting Values.
        *
        * @param[in] name SettingName.
        * @param[out] v Out Value.
        * @param[out] defaultV default Value.
        * 
        * @return Returns VkResult.
        */
        template<typename T>
        VkResult GetValues(const std::string& name, std::vector<T>& v, const std::vector<T>& defaultV);
    };

    template <typename T>
    VkResult LayerSettingSet::GetValue(const std::string& name, T& v, const T& defaultV)
    {
        if (!vkuHasLayerSetting(m_Handle, name.c_str()))
        {
            v = defaultV;
            
            return VK_SUCCESS;
        }
        
        return vkuGetLayerSettingValue(m_Handle, name.c_str(), v);
    }

    template <typename T>
    VkResult LayerSettingSet::GetValues(const std::string& name, std::vector<T>& v, const std::vector<T>& defaultV)
    {
        if (!vkuHasLayerSetting(m_Handle, name.c_str()))
        {
            v = defaultV;
            
            return VK_SUCCESS;
        }
        
        return vkuGetLayerSettingValues(m_Handle, name.c_str(), v);
    }
}
