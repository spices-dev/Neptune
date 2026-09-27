/**
* @file ComputePassEncoder.h.
* @brief The ComputePassEncoder Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

    /**
    * @brief WebGPU::Unit::ComputePassEncoder Class.
    * This class defines the WebGPU::Unit::ComputePassEncoder behaves.
    */
    class ComputePassEncoder : public Unit<WGPUComputePassEncoder>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ComputePassEncoder() = default;

        /**
        * @brief Destructor Function.
        */
        ~ComputePassEncoder() override;

        /**
        * @brief Create ComputePassEncoder.
        * 
        * @param[in] commandEncoder WGPUCommandEncoder.
        * @param[in] desc WGPUComputePassDescriptor.
        */
        void CreateComputePassEncoder(WGPUCommandEncoder commandEncoder, const WGPUComputePassDescriptor& desc);

        /**
        * @brief Set Unit name.
        * 
        * @param[in] name Unit name.
        */
        void SetName(const std::string& name) const;
        
        /**
        * @brief End ComputePass.
        */
        void EndComputePass() const;
        
        /**
        * @brief DispatchWorkgroups.
        * 
        * @param[in] workgroupCountX .
        * @param[in] workgroupCountY .
        * @param[in] workgroupCountZ .
        */
        void DispatchWorkgroups(uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) const;
        
        /**
        * @brief DispatchWorkgroupsIndirect.
        * 
        * @param[in] indirectBuffer WGPUBuffer.
        * @param[in] indirectOffset .
        */
        void DispatchWorkgroupsIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset) const;
        
        /**
        * @brief InsertDebugMarker.
        * 
        * @param[in] markerLabel .
        */
        void InsertDebugMarker(const std::string& markerLabel) const;
        
        /**
        * @brief PushDebugGroup.
        * 
        * @param[in] groupLabel .
        */
        void PushDebugGroup(const std::string& groupLabel) const;
        
        /**
        * @brief PopDebugGroup.
        */
        void PopDebugGroup() const;
        
        /**
        * @brief SetBindGroup.
        * 
        * @param[in] groupIndex .
        * @param[in] group WGPUBindGroup.
        * @param[in] dynamicOffsets .
        */
        void SetBindGroup(uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsets = 0) const;
        
        /**
        * @brief SetImmediates.
        * 
        * @param[in] offset .
        * @param[in] data .
        * @param[in] size .
        */
        void SetImmediates(uint32_t offset, const void* data, size_t size) const;
        
        /**
        * @brief WriteTimestamp.
        * 
        * @param[in] querySet WGPUQuerySet.
        * @param[in] queryIndex .
        */
        void WriteTimestamp(WGPUQuerySet querySet, uint32_t queryIndex) const;
        
        /**
        * @brief Set Pipeline.
        *
        * @param[in] pipeline WGPUComputePipeline.
        */
        void SetPipeline(WGPUComputePipeline pipeline) const;
        
    };
}

#endif