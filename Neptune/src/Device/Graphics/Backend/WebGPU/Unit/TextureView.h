/**
* @file TextureView.h.
* @brief The TextureView Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::TextureView Class.
    * This class defines the WebGPU::Unit::TextureView behaves.
    */
    class TextureView : public Unit<WGPUTextureView>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        TextureView() = default;

        /**
        * @brief Destructor Function.
        */
        ~TextureView() override;

        /**
        * @brief Create TextureView.
        * 
        * @param[in] texture WGPUTexture.
        * @param[in] desc WGPUTextureViewDescriptor.
        */
        void CreateTextureView(WGPUTexture texture, const WGPUTextureViewDescriptor& desc);
		
        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
    };
}

#endif