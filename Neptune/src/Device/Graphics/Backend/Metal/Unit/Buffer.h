/**
* @file Buffer.h.
* @brief The Buffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::Buffer Class.
    * This class defines the Metal::Unit::Buffer behaves.
    */
    class Buffer : public Unit<MTLBuffer>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Buffer() = default;

        /**
        * @brief Destructor Function.
        */
        ~Buffer() override;
        
    };
}

#endif