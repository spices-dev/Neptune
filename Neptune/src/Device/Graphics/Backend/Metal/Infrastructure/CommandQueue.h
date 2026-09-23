/**
* @file CommandQueue.h.
* @brief The CommandQueue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Metal/Unit/CommandQueue.h"

namespace Neptune::Metal {

    using ICommandQueue = IInfrastructure<class CommandQueue, EInfrastructure::CommandQueue>;

    /**
    * @brief Metal::CommandQueue Class.
    * This class defines the Metal::CommandQueue behaves.
    */
    class CommandQueue : public Infrastructure
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] context Context.
        * @param[in] e EInfrastructure.
        */
        CommandQueue(Context& context, EInfrastructure e);

        /**
        * @brief Destructor Function.
        */
        ~CommandQueue() override = default;

        /**
        * @brief Get Unit Handle.
        *
        * @return Returns Unit Handle.
        */
        const Unit::CommandQueue::Handle& Handle() const { return m_CommandQueue.GetHandle(); }
        
    private:
        
        /**
        * @brief Create CommandQueue.
        */
        void Create();
        
    private:

        Unit::CommandQueue m_CommandQueue;  // @brief this CommandQueue.
    };
	
}

#endif