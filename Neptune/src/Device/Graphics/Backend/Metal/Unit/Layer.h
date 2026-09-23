/**
* @file Layer.h.
* @brief The Layer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::Layer Class.
    * This class defines the Metal::Unit::Layer behaves.
    */
    class Layer : public Unit<MTLLayer>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Layer() = default;

        /**
        * @brief Destructor Function.
        */
        ~Layer() override;
        
        /**
        * @brief Create Layer.
        */
        void CreateLayer();
        
    };
}

#endif