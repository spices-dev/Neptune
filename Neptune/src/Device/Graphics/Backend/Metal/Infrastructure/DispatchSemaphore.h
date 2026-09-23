/**
* @file DispatchSemaphore.h.
* @brief The DispatchSemaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Metal/Unit/DispatchSemaphore.h"

namespace Neptune::Metal {

    using IGraphicDispatchSemaphore = IInfrastructure<class DispatchSemaphore, EInfrastructure::GraphicDispatchSemaphore>;
    using IGraphicDispatchSemaphore = IInfrastructure<class DispatchSemaphore, EInfrastructure::GraphicDispatchSemaphore>;

    /**
    * @brief Metal::DispatchSemaphore Class.
    * This class defines the Metal::DispatchSemaphore behaves.
    */
    class DispatchSemaphore : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        * @param[in] count Semaphore Spare Count.
        */
        DispatchSemaphore(Context& context, EInfrastructure e, uint32_t count);

        /**
        * @brief Destructor Function.
        */
        ~DispatchSemaphore() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::DispatchSemaphore::Handle& Handle() const { return m_DispatchSemaphore.GetHandle(); }
        
        /**
        * @brief Wait DispatchSemaphore.
        */
        void Wait();
        
        /**
        * @brief Signal DispatchSemaphore.
        */
        void Signal();
        
    private:
        
        /**
        * @brief Create DispatchSemaphore.
        * 
        * @param[in] count Semaphore Spare Count.
        */
        void Create(uint32_t count);
        
    private:

        Unit::DispatchSemaphore m_DispatchSemaphore;  // @brief this DispatchSemaphore.
    };
	
}

#endif