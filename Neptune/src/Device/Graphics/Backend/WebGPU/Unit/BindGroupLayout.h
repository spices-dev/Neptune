/**
* @file BindGroupLayout.h.
* @brief The BindGroupLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::BindGroupLayout Class.
    * This class defines the WebGPU::Unit::BindGroupLayout behaves.
    */
    class BindGroupLayout : public Unit<WGPUBindGroupLayout>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        BindGroupLayout() = default;

        /**
        * @brief Destructor Function.
        */
        ~BindGroupLayout() override;

        /**
        * @brief Create BindGroupLayout.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUBindGroupLayoutDescriptor.
        */
        void CreateBindGroupLayout(WGPUDevice device, const WGPUBindGroupLayoutDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif