/**
* @file Device.h.
* @brief The Device Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::Device Class.
    * This class defines the Metal::Unit::Device behaves.
    */
    class Device : public Unit<MTLDevice>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Device() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~Device() override;
        
        /**
        * @brief Create Device.
        */
        void CreateDevice();
        
    };
}

#endif