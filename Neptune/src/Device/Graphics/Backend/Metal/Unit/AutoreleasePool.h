/**
* @file AutoreleasePool.h.
* @brief The AutoreleasePool Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::AutoreleasePool Class.
    * This class defines the Metal::Unit::AutoreleasePool behaves.
    */
    class AutoreleasePool : public Unit<MTLAutoreleasePool>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        AutoreleasePool() = default;

        /**
        * @brief Destructor Function.
        */
        ~AutoreleasePool() override;
        
        /**
        * @brief Create AutoreleasePool.
        */
        void CreateAutoreleasePool();
        
    };
}

#endif