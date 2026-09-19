/**
* @file Timeline.h.
* @brief The Timeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Middleware/ITimeLine.h"

namespace Neptune::Vulkan {

    using IGraphicTimeLine     = IInfrastructure<class TimeLine, EInfrastructure::GraphicTimeLine>;
    using IComputeTimeLine     = IInfrastructure<class TimeLine, EInfrastructure::ComputeTimeLine>;

    /**
    * @brief Vulkan::TimeLine Class.
    * This class defines the Vulkan::TimeLine behaves.
    */
    class TimeLine : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] count Count.
        */
        TimeLine(Context& context, EInfrastructure e, uint32_t count);

        /**
        * @brief Destructor Function.
        */
        ~TimeLine() override = default;

        /**
        * @brief Wait Semaphore.
        * 
        * @param[in] value Wait Value;
        */
        void Wait(uint64_t value) const;
        
        /**
        * @brief Interface of Get Semaphore.
        * 
        * @param[in] frameId Frame Id;
        * 
        * @return Returns VkSemaphore.
        */
        VkSemaphore Semaphore(uint64_t frameId) const;
        
        /**
        * @brief Interface of Get Fence.
        * 
        * @param[in] frameId Frame Id;
        * 
        * @return Returns VkFence.
        */
        VkFence Fence(uint64_t frameId) const;
        
    private:
        
        /**
        * @brief Set TimeLine Name.
        */
        void SetName() const;
        
    private:

        UP<Middleware::ITimeLine> m_TimeLine;    // @brief this TimeLine.

    };
	
}

#endif