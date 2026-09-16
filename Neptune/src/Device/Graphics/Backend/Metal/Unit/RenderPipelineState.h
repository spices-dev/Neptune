/**
* @file RenderPipelineState.h.
* @brief The RenderPipelineState Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Metal::Unit {

    /**
    * @brief Metal::Unit::RenderPipelineState Class.
    * This class defines the Metal::Unit::RenderPipelineState behaves.
    */
    class RenderPipelineState : public Unit<MTLRenderPipelineState>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        RenderPipelineState() = default;

        /**
        * @brief Destructor Function.
        */
        ~RenderPipelineState() override;
        
        /**
        * @brief Create RenderPipelineState.
        * 
        * @param[in] device MTLDevice.
        * @param[in] desc MTLRenderPipelineDescriptor
        */
        void CreateRenderPipelineState(MTLDevice device, MTLRenderPipelineDescriptor desc);
        
    };
}

#endif