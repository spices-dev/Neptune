/**
* @file Queue.h.
* @brief The Queue Class Definitions.
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
        * 
        * @param[in] state EExtensionState.
        */
        explicit Queue(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Queue() override = default;
        
        /**
        * @brief Query PhysicalDevice Queues.
        * 
        * @param[in] device VkPhysicalDevice.
        * @param[in] surface VkSurfaceKHR.
        */
        std::unordered_set<VkQueueFlagBits> Query(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);
        
        /**
        * @brief Get Queue Family.
        * 
        * @param[in] bit VkQueueFlagBits.
        * 
        * @return Returns Queue Family.
        */
        uint32_t GetQueueFamily(VkQueueFlagBits bit) const;
        
        /**
        * @brief Get Queue Families.
        * 
        * @return Returns Queue Families.
        */
        const std::unordered_map<VkQueueFlagBits, std::pair<uint32_t, uint32_t>>& GetQueueFamilies() const { return m_QueueFamilies; }
        
        /**
        * @brief Is Queue Family Valid.
        * 
        * @param[in] bit VkQueueFlagBits.
        * 
        * @return Returns True if valid.
        */
        bool HasQueueFamily(VkQueueFlagBits bit) const { return m_QueueFamilies.contains(bit); }
        
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
        uint32_t GetPresentQueueFamily() const { return m_PresentQueueFamily.value_or(UINT32_MAX); }
        
        /**
        * @brief Is Present Queue Family Valid.
        * 
        * @return Returns True if valid.
        */
        bool HasPresentQueueFamily() const { return m_PresentQueueFamily.has_value(); }
        
    private:
        
        std::unordered_map<VkQueueFlagBits, std::pair<uint32_t, uint32_t>> m_QueueFamilies;         // @brief Queue Families.
        std::optional<uint32_t> m_PresentQueueFamily = std::nullopt;                                // @brief Present QueueFamily
    };
}

#endif