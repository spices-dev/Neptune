/**
* @file PipelineLayout.h.
* @brief The PipelineLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::PipelineLayout Class.
    * This class defines the WebGPU::Unit::PipelineLayout behaves.
    */
    class PipelineLayout : public Unit<WGPUPipelineLayout>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        PipelineLayout() = default;

        /**
        * @brief Destructor Function.
        */
        ~PipelineLayout() override;

        /**
        * @brief Create PipelineLayout.
        * 
        * @param[in] device WGPUDevice.
        * @param[in] desc WGPUPipelineLayoutDescriptor.
        */
        void CreatePipelineLayout(WGPUDevice device, const WGPUPipelineLayoutDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
    };
}

#endif