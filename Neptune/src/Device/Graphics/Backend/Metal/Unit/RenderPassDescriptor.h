/**
* @file RenderPassDescriptor.h.
* @brief The RenderPassDescriptor Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::RenderPassDescriptor Class.
    * This class defines the Metal::Unit::RenderPassDescriptor behaves.
    */
    class RenderPassDescriptor : public Unit<MTLRenderPassDescriptor>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        RenderPassDescriptor() = default;

        /**
        * @brief Destructor Function.
        */
        ~RenderPassDescriptor() override;
        
        /**
        * @brief Create RenderPassDescriptor.
        */
        void CreateRenderPassDescriptor();
    };
}

#endif