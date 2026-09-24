/**
* @file ComputePipeline.h.
* @brief The ComputePipeline Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::ComputePipeline Class.
    * This class defines the WebGPU::Unit::ComputePipeline behaves.
    */
    class ComputePipeline : public Unit<WGPUComputePipeline>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ComputePipeline() = default;

        /**
        * @brief Destructor Function.
        */
        ~ComputePipeline() override;

        /**
        * @brief Create ComputePipeline.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUComputePipelineDescriptor.
        */
        void CreateComputePipeline(WGPUDevice device, const WGPUComputePipelineDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif