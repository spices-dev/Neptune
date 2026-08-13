/**
* @file Function.h.
* @brief The Function Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::Function Class.
    * This class defines the Metal::Unit::Function behaves.
    */
    class Function : public Unit<MTLFunction>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Function() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~Function() override;
        
    };
}

#endif