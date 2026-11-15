/**
* @file CommandQueueDescriptor.h.
* @brief The CommandQueueDescriptor Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::CommandQueueDescriptor Class.
    * This class defines the Metal::Unit::CommandQueueDescriptor behaves.
    */
    class CommandQueueDescriptor : public Unit<MTLCommandQueueDescriptor>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        CommandQueueDescriptor() = default;

        /**
        * @brief Destructor Function.
        */
        ~CommandQueueDescriptor() override;
        
        /**
        * @brief Create CommandQueueDescriptor.
        */
        void CreateCommandQueueDescriptor();
    };
}

#endif
