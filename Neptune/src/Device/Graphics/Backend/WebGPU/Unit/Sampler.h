/**
* @file Sampler.h.
* @brief The Sampler Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::Sampler Class.
    * This class defines the WebGPU::Unit::Sampler behaves.
    */
    class Sampler : public Unit<WGPUSampler>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Sampler() = default;

        /**
        * @brief Destructor Function.
        */
        ~Sampler() override;

        /**
        * @brief Create Sampler.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUSamplerDescriptor.
        */
        void CreateSampler(WGPUDevice device, const WGPUSamplerDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif