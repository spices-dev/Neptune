/**
* @file Queue.cpp.
* @brief The Queue Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Queue.h"
#include "Device/Graphics/Backend/Vulkan/Converter.h"

namespace Neptune::Vulkan::Extension {
    
    bool Queue::IsQueuesSatisfied(const std::unordered_set<VkQueueFlagBits>& chains, const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
    {
        NEPTUNE_PROFILE_ZONE
        
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties2> queueFamilies(queueFamilyCount,{ VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
        vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, queueFamilies.data());
        
        std::unordered_set<uint32_t> used;
        
        std::ranges::for_each(chains, [&](const auto& bit) {
            
            bool support = false;
            
            for (uint32_t i = 0; i < queueFamilies.size(); ++i)
            {
                if (used.contains(i)) continue;
                
                const auto& property = queueFamilies[i].queueFamilyProperties;
                
                if (property.queueFlags & bit)
                {
                    m_QueueFamilies[bit] = { i, property.queueCount };
                    
                    used.insert(i);
                    
                    support = true;
                    
                    NEPTUNE_LOG_CORE(I) << "Queue [ " << Vulkan::ToString(bit) << " ] : " << i;
                    
                    break;
                }
            }
            
            if (!support)
            {
                NEPTUNE_LOG_CORE(E) << "Queue [ " << Vulkan::ToString(bit) << " ] : was not satisfied.";
            }
        });
        
        if (surface)
        {
            if (m_QueueFamilies.contains(VK_QUEUE_GRAPHICS_BIT))
            {
                auto graphic = m_QueueFamilies.at(VK_QUEUE_GRAPHICS_BIT).first;
                
                VkBool32 presentSupport = false;
                
                VULKAN_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(device, graphic, surface, &presentSupport))
                
                if (presentSupport)
                {
                    m_PresentQueueFamily = graphic;
                }
            }
            
            if (!m_PresentQueueFamily)
            {
                for (uint32_t i = 0; i < queueFamilies.size(); ++i)
                {
                    VkBool32 presentSupport = false;
                
                    VULKAN_CHECK(vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport))
            
                    if (presentSupport)
                    {
                        m_PresentQueueFamily =  i;
                        break;
                    }
                }
            }
            
            if (!m_PresentQueueFamily)
            {
                NEPTUNE_LOG_CORE(E) << "Queue [ " << "Present Queue" << " ] : was not satisfied.";
            }
        }
        
        return true;
    }
    
    uint32_t Queue::GetQueueFamily(VkQueueFlagBits bit) const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (!m_QueueFamilies.contains(bit))
        {
            return UINT32_MAX;
        }
        
        return m_QueueFamilies.at(bit).first;
    }
    
    uint32_t Queue::GetQueueFamilyCount(VkQueueFlagBits bit) const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (!m_QueueFamilies.contains(bit))
        {
            return UINT32_MAX;
        }
        
        return m_QueueFamilies.at(bit).second;
    }
}

#endif