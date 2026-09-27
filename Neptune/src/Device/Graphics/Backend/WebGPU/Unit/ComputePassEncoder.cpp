/**
* @file ComputePassEncoder.cpp.
* @brief The ComputePassEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "ComputePassEncoder.h"

namespace Neptune::WebGPU::Unit {

    ComputePassEncoder::~ComputePassEncoder()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuComputePassEncoderRelease(m_Handle);
    }

    void ComputePassEncoder::CreateComputePassEncoder(WGPUCommandEncoder commandEncoder, const WGPUComputePassDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuCommandEncoderBeginComputePass(commandEncoder, &desc);
    }

    void ComputePassEncoder::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuComputePassEncoderSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
    void ComputePassEncoder::EndComputePass() const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuComputePassEncoderEnd(m_Handle);
    }

    void ComputePassEncoder::DispatchWorkgroups(uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuComputePassEncoderDispatchWorkgroups(m_Handle, workgroupCountX, workgroupCountY, workgroupCountZ);
    }

    void ComputePassEncoder::DispatchWorkgroupsIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset) const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuComputePassEncoderDispatchWorkgroupsIndirect(m_Handle, indirectBuffer, indirectOffset);
    }

    void ComputePassEncoder::InsertDebugMarker(const std::string& markerLabel) const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuComputePassEncoderInsertDebugMarker(m_Handle, { markerLabel.c_str(), WGPU_STRLEN });
    }

    void ComputePassEncoder::PushDebugGroup(const std::string& groupLabel) const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuComputePassEncoderPushDebugGroup(m_Handle, { groupLabel.c_str(), WGPU_STRLEN });
    }

    void ComputePassEncoder::PopDebugGroup() const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuComputePassEncoderPopDebugGroup(m_Handle);
    }

    void ComputePassEncoder::SetBindGroup(uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsets) const
    {
        NEPTUNE_PROFILE_ZONE
        
        if (dynamicOffsets == 0)
        {
            wgpuComputePassEncoderSetBindGroup(m_Handle, groupIndex, group, 0, nullptr);
        }
        else
        {
            wgpuComputePassEncoderSetBindGroup(m_Handle, groupIndex, group, 1, &dynamicOffsets);
        }
    }

    void ComputePassEncoder::WriteTimestamp(WGPUQuerySet querySet, uint32_t queryIndex) const
    {
        NEPTUNE_PROFILE_ZONE
        
        wgpuComputePassEncoderWriteTimestamp(m_Handle, querySet, queryIndex);
    }

    void ComputePassEncoder::SetPipeline(WGPUComputePipeline pipeline) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuComputePassEncoderSetPipeline(m_Handle, pipeline);
    }
}

#endif