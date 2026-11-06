/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Vulkan/Infrastructure/Infrastructure.h"
#include "Vulkan/Unit/CommandPool.h"
#include "Vulkan/Unit/CommandBuffer.h"
#include "Vulkan/Unit/Semaphore.h"
#include "Enum.h"

namespace Neptune::Vulkan {

    using ICommandBuffer = IInfrastructure<MultiInstance<uint32_t, class CommandBuffer>, EInfrastructure::SwapChain>;
	
    /**
    * @brief Vulkan::CommandBuffer Class.
    * This class defines the Vulkan::CommandBuffer behaves.
    */
    class CommandBuffer : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        */
        CommandBuffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~CommandBuffer() override = default;
        
        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::CommandBuffer::Handle& Handle() const { return m_CommandBuffer->GetHandle(); }
        
        /**
        * @brief Get Semaphore Unit Handle.
        *
        * @return Returns Semaphore Unit Handle.
        */
        const Unit::Semaphore::Handle& Semaphore() const { return m_Semaphore->GetHandle(); }
        
    public:

        UP<Unit::CommandPool>   m_CommandPool;     // @brief CommandPool.
        UP<Unit::CommandBuffer> m_CommandBuffer;   // @brief CommandBuffer.
        UP<Unit::Semaphore>     m_Semaphore;       // @brief Semaphore.
    };

}