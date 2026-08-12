/**
* @file CommandQueue.h.
* @brief The CommandQueue Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::CommandQueue Class.
    * This class defines the Metal::Unit::CommandQueue behaves.
    */
    class CommandQueue : public Unit<MTLDevice>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        CommandQueue() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~CommandQueue() override;
        
    };
}

#endif