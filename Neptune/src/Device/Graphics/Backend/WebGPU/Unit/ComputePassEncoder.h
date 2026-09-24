/**
* @file ComputePassEncoder.h.
* @brief The ComputePassEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::ComputePassEncoder Class.
    * This class defines the WebGPU::Unit::ComputePassEncoder behaves.
    */
    class ComputePassEncoder : public Unit<WGPUComputePassEncoder>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ComputePassEncoder() = default;

        /**
        * @brief Destructor Function.
        */
        ~ComputePassEncoder() override;

        /**
        * @brief Create ComputePassEncoder.
        * 
        * @param[in] commandEncoder WGPUCommandEncoder.
        * @param[in] desc WGPUComputePassDescriptor.
        */
        void CreateComputePassEncoder(WGPUCommandEncoder commandEncoder, const WGPUComputePassDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif