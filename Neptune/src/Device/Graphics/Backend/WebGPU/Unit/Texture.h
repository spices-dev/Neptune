/**
* @file Texture.h.
* @brief The Texture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::Texture Class.
    * This class defines the WebGPU::Unit::Texture behaves.
    */
    class Texture : public Unit<WGPUTexture>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        Texture() = default;

        /**
        * @brief Destructor Function.
        */
        ~Texture() override;

        /**
        * @brief Create Texture.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUTextureDescriptor.
        */
        void CreateTexture(WGPUDevice device, const WGPUTextureDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
    };
}

#endif