/**
* @file LayerSettingSet.cpp.
* @brief The LayerSettingSet Class Implementation.
* @author Spices.
*/

#include "LayerSettingSet.h"

namespace Neptune::Vulkan::Unit {

    LayerSettingSet::~LayerSettingSet()
    {
        if (!m_Handle) return;

        vkuDestroyLayerSettingSet(m_Handle, m_Life.allocator);
    }
    
    VkResult LayerSettingSet::CreateLayerSettingSet(const char* name, const VkLayerSettingsCreateInfoEXT* info)
    {
        return vkuCreateLayerSettingSet(name, info, m_Life.allocator, nullptr, &m_Handle);
    }
}