/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Resource/TimelineSemaphore.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Queue.h"

namespace Neptune::Vulkan::Resource {

    /**
    * @brief Vulkan::Queue Class.
    * This class defines the Vulkan::Queue behaves.
    */
    class Queue : public ContextAccessor
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit Queue(Context& context) : ContextAccessor(context), m_Semaphore(context) {}

        /**
        * @brief Destructor Function.
        */
        ~Queue() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::Queue::Handle& Handle() const { return m_Queue.GetHandle(); }
        
        /**
        * @brief Create Queue.
        * 
        * @param[in] queue Unit::Queue::Handle.
        */
        void CreateQueue(Unit::Queue::Handle queue);
		
        /**
        * @brief Submit.
        * 
        * @param[in] info VkSubmitInfo.
        */
        void Submit(const VkSubmitInfo& info) const;
        
        /**
        * @brief Submit2.
        * 
        * @param[in] commandBuffer VkCommandBuffer.
        */
        void Submit2(VkCommandBuffer commandBuffer) const;
        
        /**
        * @brief Wait Queue.
        */
        void WaitQueue() const;
        
        /**
        * @brief Wait Semaphore.
        */
        void WaitSemaphore();
        
        /**
        * @brief Set Name.
        * 
        * @param[in] name .
        */
        void SetName(const std::string& name) const;
        
    private:
        
        Unit::Queue           m_Queue;         // @brief This Queue.
        TimelineSemaphore     m_Semaphore;     // @brief This Semaphore.
    };
}

#endif