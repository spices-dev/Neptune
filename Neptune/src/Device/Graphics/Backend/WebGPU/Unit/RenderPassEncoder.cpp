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
}

#endif