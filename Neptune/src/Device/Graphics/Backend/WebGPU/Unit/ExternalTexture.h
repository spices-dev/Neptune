/**
* @file ExternalTexture.h.
* @brief The ExternalTexture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::ExternalTexture Class.
    * This class defines the WebGPU::Unit::ExternalTexture behaves.
    */
    class ExternalTexture : public Unit<WGPUExternalTexture>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ExternalTexture() = default;

        /**
        * @brief Destructor Function.
        */
        ~ExternalTexture() override;

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif