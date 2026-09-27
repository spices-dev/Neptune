/**
* @file CmdList2.cpp.
* @brief The CmdList2 Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "CmdList2.h"
#include "Device/Graphics/Backend/WebGPU/Unit/CommandEncoder.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Future.h"
#include "Device/Graphics/Backend/WebGPU/Unit/CommandBuffer.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Queue.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Instance.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"

namespace Neptune::WebGPU {
	
	void CmdList2::End()
	{
		NEPTUNE_PROFILE_ZONE
		
		m_CommandBuffer = CreateUP<Unit::CommandBuffer>();
        
		WGPUCommandBufferDescriptor desc{};
        
		m_CommandBuffer->SetHandle(wgpuCommandEncoderFinish(m_CommandEncoder->GetHandle(), &desc));
        
		DEBUGUTILS_SETOBJECTNAME(*m_CommandBuffer, "CommandBuffer")
		
		m_CommandEncoder.reset();
	}

	void CmdList2::SubmitWait()
	{
		NEPTUNE_PROFILE_ZONE
        
		wgpuQueueSubmit(GetContext().Get<IQueue>()->Handle(), 1, &m_CommandBuffer->GetHandle());
        
		m_CommandBuffer.reset();
		
		WGPUQueueWorkDoneCallbackInfo        info{};
		info.mode                          = WGPUCallbackMode_WaitAnyOnly;
		info.userdata1                     = nullptr;
		info.callback                      = nullptr;
		
		auto feature = CreateUP<Unit::Future>();
        
		feature->SetHandle(wgpuQueueOnSubmittedWorkDone(GetContext().Get<IQueue>()->Handle(), info));
		
		feature->Wait(GetContext().Get<IInstance>()->Handle());
	}

	void CmdList2::SetGraphicCmdList()
	{
		NEPTUNE_PROFILE_ZONE

		m_CommandEncoder = CreateSP<Unit::CommandEncoder>();
        
		WGPUCommandEncoderDescriptor desc{};
        
		m_CommandEncoder->CreateCommandEncoder(GetContext().Get<IDevice>()->Handle(), desc);
        
		DEBUGUTILS_SETOBJECTNAME(*m_CommandEncoder, "CmdList2CommandEncoder")
		
		m_RenderBindPoint = true;
	}
	
}

#endif