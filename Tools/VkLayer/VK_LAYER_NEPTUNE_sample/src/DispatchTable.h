/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/DispatchTable.h"
#include "LayerSetting.h"
#include "Enum.h"

namespace Neptune {
    
    /**
    * @brief DispatchTable
    */
    using DispatchTable = Vulkan::DispatchTable<EInfrastructure>;
    
    /**
    * @brief Get Layer Name.
    * 
    * @return Returns Layer Name.
    */
    template <>
    inline char* DispatchTable::GetName() { static char name[] = "VK_LAYER_NEPTUNE_sample"; return name; }
    
    /**
    * @brief Interface of Init Context.
    */
    template <>
    inline void DispatchTable::InitContext() {}
    
    /**
    * @brief Interface of Init Settings.
    * 
    * @param[in] setting Resource::LayerSetting.
    * 
    * @return Returns VkResult.
    */
    template <>
    inline VkResult DispatchTable::InitSettings(UP<Resource::LayerSetting>& setting)
    {
        auto data = CreateSP<Settings>();
        
        VULKAN_CHECK(setting->GetValue("welcome", data->welcome, std::string("not find")))
        
        setting->SetSetting(data);
        
        return VK_SUCCESS;
    }
    
    /**
    * @brief Interface of Dispatch Instance Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::InstanceDispatch(const char* pName) { NEPTUNE_LOG_CORE(I) << "InstanceDispatch"; return nullptr; }
        
    /**
    * @brief Interface of Dispatch Device Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::DeviceDispatch(const char* pName) { NEPTUNE_LOG_CORE(I) << "DeviceDispatch"; return nullptr; }
}
