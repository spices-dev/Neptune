/**
* @file RenderBundle.h.
* @brief The RenderBundle Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::RenderBundle Class.
    * This class defines the WebGPU::Unit::RenderBundle behaves.
    */
    class RenderBundle : public Unit<WGPURenderBundle>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        RenderBundle() = default;

        /**
        * @brief Destructor Function.
        */
        ~RenderBundle() override;

        /**
        * @brief Create RenderBundle.
        * 
        * @param[in] renderBundleEncoder WGPURenderBundleEncoder.
        * @param[in] desc WGPURenderBundleDescriptor.
        */
        void CreateRenderBundle(WGPURenderBundleEncoder renderBundleEncoder, const WGPURenderBundleDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif