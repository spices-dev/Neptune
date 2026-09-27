/**
* @file RenderPassEncoder.cpp.
* @brief The RenderPassEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "RenderPassEncoder.h"

namespace Neptune::WebGPU::Unit {

	RenderPassEncoder::~RenderPassEncoder()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuRenderPassEncoderRelease(m_Handle);
	}
	
	void RenderPassEncoder::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
    	
		wgpuRenderPassEncoderSetLabel(m_Handle, { name.c_str(), name.size() });
	}

	void RenderPassEncoder::EndRenderPass() const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderEnd(m_Handle);
	}

	void RenderPassEncoder::BeginOcclusionQuery(uint32_t queryIndex) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderBeginOcclusionQuery(m_Handle, queryIndex);
	}

	void RenderPassEncoder::EndOcclusionQuery() const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderEndOcclusionQuery(m_Handle);
	}

	void RenderPassEncoder::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderDraw(m_Handle, vertexCount, instanceCount, firstVertex, firstInstance);
	}

	void RenderPassEncoder::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderDrawIndexed(m_Handle, indexCount, instanceCount, firstIndex, baseVertex, firstInstance);
	}

	void RenderPassEncoder::DrawIndexedIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderDrawIndexedIndirect(m_Handle, indirectBuffer, indirectOffset);
	}

	void RenderPassEncoder::DrawIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderDrawIndirect(m_Handle, indirectBuffer, indirectOffset);
	}

	void RenderPassEncoder::ExecuteBundles(size_t bundleCount, const WGPURenderBundle& bundles) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderExecuteBundles(m_Handle, bundleCount, &bundles);
	}

	void RenderPassEncoder::InsertDebugMarker(const std::string& markerLabel) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderInsertDebugMarker(m_Handle, { markerLabel.c_str(), WGPU_STRLEN });
	}

	void RenderPassEncoder::MultiDrawIndexedIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderMultiDrawIndexedIndirect(m_Handle, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset);
	}

	void RenderPassEncoder::MultiDrawIndirect(WGPUBuffer indirectBuffer, uint64_t indirectOffset, uint32_t maxDrawCount, WGPUBuffer drawCountBuffer, uint64_t drawCountBufferOffset) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderMultiDrawIndirect(m_Handle, indirectBuffer, indirectOffset, maxDrawCount, drawCountBuffer, drawCountBufferOffset);
	}

	void RenderPassEncoder::PushDebugGroup(const std::string& groupLabel) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderPushDebugGroup(m_Handle, { groupLabel.c_str(), WGPU_STRLEN });
	}

	void RenderPassEncoder::PopDebugGroup() const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderPopDebugGroup(m_Handle);
	}

	void RenderPassEncoder::SetBindGroup(uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsets) const
	{
		NEPTUNE_PROFILE_ZONE
		
		if (dynamicOffsets == 0)
		{
			wgpuRenderPassEncoderSetBindGroup(m_Handle, groupIndex, group, 0, nullptr);
		}
		else
		{
			wgpuRenderPassEncoderSetBindGroup(m_Handle, groupIndex, group, 1, &dynamicOffsets);
		}
	}

	void RenderPassEncoder::SetBlendConstant(WGPUColor color) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderSetBlendConstant(m_Handle, &color);
	}

	void RenderPassEncoder::SetIndexBuffer(WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderSetIndexBuffer(m_Handle, buffer, format, offset, size);
	}

	void RenderPassEncoder::SetStencilReference(uint32_t reference) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderSetStencilReference(m_Handle, reference);
	}

	void RenderPassEncoder::SetVertexBuffer(uint32_t slot, WGPUBuffer buffer, uint64_t offset, uint64_t size) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderSetVertexBuffer(m_Handle, slot, buffer, offset, size);
	}

	void RenderPassEncoder::WriteTimestamp(WGPUQuerySet querySet, uint32_t queryIndex) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderWriteTimestamp(m_Handle, querySet, queryIndex);
	}

	void RenderPassEncoder::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float minDepth, float maxDepth) const
	{
		NEPTUNE_PROFILE_ZONE

		wgpuRenderPassEncoderSetViewport(m_Handle, static_cast<float>(x), static_cast<float>(y), static_cast<float>(width), static_cast<float>(height), minDepth, maxDepth);
	}

	void RenderPassEncoder::SetScissor(uint32_t x, uint32_t y, uint32_t width, uint32_t height) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderSetScissorRect(m_Handle, x, y, width, height);
	}

	void RenderPassEncoder::SetPipeline(WGPURenderPipeline pipeline) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuRenderPassEncoderSetPipeline(m_Handle, pipeline);
	}
}

#endif