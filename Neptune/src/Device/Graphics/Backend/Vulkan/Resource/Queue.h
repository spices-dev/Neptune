/**
* @file Queue.h.
* @brief The Queue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/ITimeLine.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/IQueueSubmit.h"
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
        explicit Queue(Context& context);

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
        * @param[in] commandBuffer VkCommandBuffer.
        */
        void Submit(VkCommandBuffer commandBuffer);
        
        /**
        * @brief WaitTimeLine.
        */
        void WaitTimeLine() const;
        
        /**
        * @brief Wait.
        */
        void Wait() const;
        
        /**
        * @brief Set Name.
        * 
        * @param[in] name .
        */
        void SetName(const std::string& name) const;
        
    private:
        
        Unit::Queue                  m_Queue;            // @brief This Queue.
        UP<Middleware::ITimeLine>    m_TimeLine;         // @brief This TimeLine.
        UP<Middleware::IQueueSubmit> m_QueueSubmit;      // @brief This QueueSubmit.
        uint64_t                     m_Time = 0;         // @brief This TimeLine Time.
    };
}

#endif