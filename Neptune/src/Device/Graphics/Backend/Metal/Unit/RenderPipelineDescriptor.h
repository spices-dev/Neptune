/**
* @file RenderPipelineDescriptor.h.
* @brief The RenderPipelineDescriptor Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::RenderPipelineDescriptor Class.
    * This class defines the Metal::Unit::RenderPipelineDescriptor behaves.
    */
    class RenderPipelineDescriptor : public Unit<MTLRenderPipelineDescriptor>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        RenderPipelineDescriptor() : Unit() {}

        /**
        * @brief Destructor Function.
        */
        ~RenderPipelineDescriptor() override;
        
        /**
        * @brief Create RenderPipelineDescriptor.
        */
        void CreateRenderPipelineDescriptor();
    };
}

#endif