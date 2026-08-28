/**
* @file Queue.h.
* @brief The Queue Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    class Queue;
    
    using IQueue = IExtension<Queue, EExtension::Queue>;
    
    class Queue : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        Queue() = default;
        
        /**
        * @brief Destructor Function.
        */
        ~Queue() override = default;
        
        /**
        * @brief Is Device Queues satisfied.
        * 
        * @param[in] chains VkQueueFlagBits.
        * @param[in] device VkDevice.
        * @param[in] surface VkSurfaceKHR_T.
        * 
        * @return Returns true if satisfied.
        */
        bool IsQueuesSatisfied(const std::unordered_set<VkQueueFlagBits>& chains, const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
        
        /**
        * @brief Get Queue Family.
        * 
        * @param[in] bit VkQueueFlagBits.
        * 
        * @return Returns Queue Family.
        */
        uint32_t GetQueueFamily(VkQueueFlagBits bit) const;
        
        /**
        * @brief Get Queue Family Count.
        * 
        * @param[in] bit VkQueueFlagBits.
        * 
        * @return Returns Queue Family Count.
        */
        uint32_t GetQueueFamilyCount(VkQueueFlagBits bit) const;
        
        /**
        * @brief Get Present Queue Family.
        * 
        * @return Returns Present Queue Family.
        */
        uint32_t GetPresentQueueFamil() const { return m_PresentQueueFamily.value_or(UINT32_MAX); }
        
    private:
        
        std::unordered_map<VkQueueFlagBits, std::pair<uint32_t, uint32_t>> m_QueueFamilies;         // @brief Queue Families.
        std::optional<uint32_t> m_PresentQueueFamily = std::nullopt;                                // @brief Present QueueFamily
    };
}

#endif