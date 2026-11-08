/**
* @file LayerSetting.cpp.
* @brief The LayerSetting Class Implementation.
* @author Spices.
*/

#include "LayerSetting.h"

namespace Neptune::Vulkan::Resource {
    
    void LayerSetting::CreateLayerSettingSet(const char* name, const VkInstanceCreateInfo& info, const VkAllocationCallbacks* pAllocator)
    {
        auto* settingInfo = vkuFindLayerSettingsCreateInfo(&info);
            
        m_LayerSettingSet.SetLife({ pAllocator });
            
        m_LayerSettingSet.CreateLayerSettingSet(name, settingInfo);
    }
}