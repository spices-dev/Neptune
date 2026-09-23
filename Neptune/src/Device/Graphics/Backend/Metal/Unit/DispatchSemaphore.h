/**
* @file DispatchSemaphore.h.
* @brief The DispatchSemaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::DispatchSemaphore Class.
    * This class defines the Metal::Unit::DispatchSemaphore behaves.
    */
    class DispatchSemaphore : public Unit<dispatch_semaphore_t>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        DispatchSemaphore() = default;

        /**
        * @brief Destructor Function.
        */
        ~DispatchSemaphore() override;
        
        /**
        * @brief Create DispatchSemaphore.
        * 
        * @param[in] count Semaphore Spare Count.
        */
        void CreateDispatchSemaphore(uint32_t count);
        
        /**
        * @brief Wait DispatchSemaphore.
        */
        void Wait();
        
        /**
        * @brief Signal DispatchSemaphore.
        */
        void Signal();
    };
}

#endif