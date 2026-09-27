/**
* @file CommandEncoder.cpp.
* @brief The CommandEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "CommandEncoder.h"

namespace Neptune::WebGPU::Unit {

	CommandEncoder::~CommandEncoder()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		wgpuCommandEncoderRelease(m_Handle);
	}

	void CommandEncoder::CreateCommandEncoder(WGPUDevice device,  const WGPUCommandEncoderDescriptor& desc)
	{
		NEPTUNE_PROFILE_ZONE

		m_Handle = wgpuDeviceCreateCommandEncoder(device, &desc);
	}
	
	void CommandEncoder::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuCommandEncoderSetLabel(m_Handle, { name.c_str(), name.size() });
	}
	
	WGPURenderPassEncoder CommandEncoder::BeginRenderPass(const WGPURenderPassDescriptor& desc) const
	{
		NEPTUNE_PROFILE_ZONE

		return wgpuCommandEncoderBeginRenderPass(m_Handle, &desc);
	}

	WGPUComputePassEncoder CommandEncoder::BeginComputePass(const WGPUComputePassDescriptor& desc) const
	{
		NEPTUNE_PROFILE_ZONE

		return wgpuCommandEncoderBeginComputePass(m_Handle, &desc);
	}
	
	void CommandEncoder::CopyTextureToTexture(const WGPUTexelCopyTextureInfo& source, const WGPUTexelCopyTextureInfo& destination, const WGPUExtent3D& copySize) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuCommandEncoderCopyTextureToTexture(m_Handle, &source, &destination, &copySize);
	}
	
	void CommandEncoder::CopyBufferToBuffer(WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) const
	{
		NEPTUNE_PROFILE_ZONE
		
		wgpuCommandEncoderCopyBufferToBuffer(m_Handle, source, sourceOffset, destination, destinationOffset, size);
	}
}

#endif