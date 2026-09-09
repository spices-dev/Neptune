/**
* @file TimelineSemaphore.h.
* @brief The TimelineSemaphore Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Semaphore.h"

namespace Neptune::Vulkan::Resource {

    /**
    * @brief Vulkan::TimelineSemaphore Class.
    * This class defines the Vulkan::TimelineSemaphore behaves.
    */
    class TimelineSemaphore : public ContextAccessor
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        */
        explicit TimelineSemaphore(Context& context) : ContextAccessor(context) {}

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
        * @brief Create Semaphore.
        */
        void CreateSemaphore();
		
        /**
        * @brief Wait Semaphore.
        */
        void Wait();
		
        /**
        * @brief Signal Semaphore.
        */
        void Signal() const;
        
        /**
        * @brief Next Signal Value.
        * 
        * @return Returns Next Signal Value
        */
        uint64_t Next() const { return m_Id; }
        
        /**
        * @brief Set Name.
        *
        * @param[in] name .
        */
        void SetName(const std::string& name) const;

    private:
        
        Unit::Semaphore       m_Semaphore;       // @brief This Semaphore.
        uint64_t              m_Id = 1;          // @brief Semaphore id.
    };
}

#endif