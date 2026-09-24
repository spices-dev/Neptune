/**
* @file BindGroup.h.
* @brief The BindGroup Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::BindGroup Class.
    * This class defines the WebGPU::Unit::BindGroup behaves.
    */
    class BindGroup : public Unit<WGPUBindGroup>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        BindGroup() = default;

        /**
        * @brief Destructor Function.
        */
        ~BindGroup() override;

        /**
        * @brief Create BindGroup.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUBindGroupDescriptor.
        */
        void CreateBindGroup(WGPUDevice device, const WGPUBindGroupDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif