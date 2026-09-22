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
	
	WGPURenderPassEncoder CommandEncoder::BeginRenderPass(const WGPURenderPassDescriptor& info) const
	{
		NEPTUNE_PROFILE_ZONE

		return wgpuCommandEncoderBeginRenderPass(m_Handle, &info);
	}
}

#endif