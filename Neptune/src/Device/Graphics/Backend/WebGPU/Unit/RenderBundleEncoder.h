/**
* @file RenderBundleEncoder.h.
* @brief The RenderBundleEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::RenderBundleEncoder Class.
    * This class defines the WebGPU::Unit::RenderBundleEncoder behaves.
    */
    class RenderBundleEncoder : public Unit<WGPURenderBundleEncoder>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        RenderBundleEncoder() = default;

        /**
        * @brief Destructor Function.
        */
        ~RenderBundleEncoder() override;

        /**
        * @brief Create RenderBundleEncoder.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPURenderBundleEncoderDescriptor.
        */
        void CreateRenderBundleEncoder(WGPUDevice device, const WGPURenderBundleEncoderDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
    };
}

#endif