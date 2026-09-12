/**
* @file SpinLock.hpp.
* @brief The SpinLock Class Definitions and Implementation.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune::Container {

    /**
    * @brief Spin Lock.
    */
    class SpinLock
    {
    public:
        
        NONE_COPY(SpinLock)
        
    public:

        /**
        * @brief Constructor Function.
        */
        SpinLock() = default;

        /**
        * @brief Destructor Function.
        */
        ~SpinLock() = default;

        /**
        * @brief Get Lock.
        */
        void lock()
        {
            while (m_Flag.test_and_set(std::memory_order_acquire))
            {
                while (m_Flag.test(std::memory_order_relaxed)){}
            }
        }

        /**
        * @brief Release Lock.
        */
        void unlock()
        {
            m_Flag.clear(std::memory_order_release);
        }
        
    private:
        
        std::atomic_flag m_Flag = ATOMIC_FLAG_INIT;  // @brief Spin Lock atomic flag.

    };

}
