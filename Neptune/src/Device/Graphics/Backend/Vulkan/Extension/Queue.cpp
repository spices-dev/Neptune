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
    
    namespace {
        
        constexpr std::array s_Chains {
            VK_QUEUE_GRAPHICS_BIT,
            VK_QUEUE_COMPUTE_BIT,
            VK_QUEUE_TRANSFER_BIT,
            VK_QUEUE_SPARSE_BINDING_BIT,
            VK_QUEUE_PROTECTED_BIT,
            VK_QUEUE_VIDEO_DECODE_BIT_KHR,
            VK_QUEUE_VIDEO_ENCODE_BIT_KHR,
            VK_QUEUE_OPTICAL_FLOW_BIT_NV,
            VK_QUEUE_DATA_GRAPH_BIT_ARM
        };
    }
    
    std::unordered_set<VkQueueFlagBits> Queue::Query(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
    {
        NEPTUNE_PROFILE_ZONE
        
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties2> queueFamilies(queueFamilyCount,{ VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2 });
        vkGetPhysicalDeviceQueueFamilyProperties2(device, &queueFamilyCount, queueFamilies.data());
        
        std::unordered_set found(s_Chains.begin(), s_Chains.end());
        
        std::unordered_set<uint32_t> used;
        
        std::ranges::for_each(s_Chains, [&](const auto& bit) {
            
            for (uint32_t i = 0; i < queueFamilies.size(); ++i)
            {
                if (used.contains(i)) continue;
                
                const auto& property = queueFamilies[i].queueFamilyProperties;
                
                if (property.queueCount == 0) continue;
                
                if (property.queueFlags & bit)
                {
                    m_QueueFamilies[bit] = { i, property.queueCount };
                    
                    used.insert(i);
                    
                    NEPTUNE_LOG_CORE(I) << "Queue [ " << Vulkan::ToString(bit) << " ] : " << i;
                    
                    return;
                }
            }
            
            for (uint32_t i = 0; i < queueFamilies.size(); ++i)
            {
                if (!used.contains(i)) continue;
                
                const auto& property = queueFamilies[i].queueFamilyProperties;
                
                if (property.queueCount == 0) continue;
                
                if (property.queueFlags & bit)
                {
                    m_QueueFamilies[bit] = { i, property.queueCount };
                    
                    used.insert(i);
                    
                    NEPTUNE_LOG_CORE(I) << "Queue [ " << Vulkan::ToString(bit) << " ] : " << i;
                    
                    return;
                }
            }
            
            found.erase(bit);
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
                    const auto& property = queueFamilies[i].queueFamilyProperties;
                    
                    if (property.queueCount == 0) continue;
                    
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
        
        return found;
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