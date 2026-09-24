/**
* @file ShaderModule.h.
* @brief The ShaderModule Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::ShaderModule Class.
    * This class defines the WebGPU::Unit::ShaderModule behaves.
    */
    class ShaderModule : public Unit<WGPUShaderModule>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ShaderModule() = default;

        /**
        * @brief Destructor Function.
        */
        ~ShaderModule() override;

        /**
        * @brief Create ShaderModule.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUShaderModuleDescriptor.
        */
        void CreateShaderModule(WGPUDevice device, const WGPUShaderModuleDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif