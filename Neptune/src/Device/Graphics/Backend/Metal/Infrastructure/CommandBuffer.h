/**
* @file CommandBuffer.h.
* @brief The CommandBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Metal/Unit/CommandBuffer.h"

namespace Neptune::Metal {

    using ICommandBuffer = IInfrastructure<class CommandBuffer, EInfrastructure::CommandBuffer>;

    /**
    * @brief Metal::CommandBuffer Class.
    * This class defines the Metal::CommandBuffer behaves.
    */
    class CommandBuffer : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        CommandBuffer(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~CommandBuffer() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::CommandBuffer::Handle& Handle() const { return m_CommandBuffer.GetHandle(); }
        
    private:
        
        /**
        * @brief Create CommandBuffer.
        */
        void Create();
        
    private:

        Unit::CommandBuffer m_CommandBuffer;  // @brief this CommandBuffer.
    };
	
}

#endif