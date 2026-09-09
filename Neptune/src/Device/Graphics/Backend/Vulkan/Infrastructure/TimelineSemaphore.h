/**
* @file TimelineSemaphore.h.
* @brief The TimelineSemaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Semaphore.h"

namespace Neptune::Vulkan {

    using IGraphicTimelineSemaphore     = IInfrastructure<class TimelineSemaphore, EInfrastructure::GraphicTimelineSemaphore>;
    using IComputeTimelineSemaphore     = IInfrastructure<class TimelineSemaphore, EInfrastructure::ComputeTimelineSemaphore>;

    /**
    * @brief Vulkan::Timeline Class.
    * This class defines the Vulkan::Timeline behaves.
    */
    class TimelineSemaphore : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        TimelineSemaphore(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~TimelineSemaphore() override = default;

        /**
        * @brief Get Unit Handle.
        * 
        * @return Returns Unit Handle.
        */
        const Unit::Semaphore::Handle& Handle() const { return m_Semaphore.GetHandle(); }

        /**
        * @brief Wait Semaphore.
        * 
        * @param[in] value Wait Value;
        */
        void Wait(uint64_t value) const;
        
    private:

        /**
        * @brief Create Fence.
        */
        void Create();

    private:

        Unit::Semaphore m_Semaphore;    // @brief this Semaphore.

    };
	
}

#endif