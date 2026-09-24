/**
* @file RenderPipeline.h.
* @brief The RenderPipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::RenderPipeline Class.
    * This class defines the WebGPU::Unit::RenderPipeline behaves.
    */
    class RenderPipeline : public Unit<WGPURenderPipeline>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        RenderPipeline() = default;

        /**
        * @brief Destructor Function.
        */
        ~RenderPipeline() override;

        /**
        * @brief Create RenderPipeline.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPURenderPipelineDescriptor.
        */
        void CreateRenderPipeline(WGPUDevice device, const WGPURenderPipelineDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif