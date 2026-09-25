/**
* @file CommandEncoder.cpp.
* @brief The CommandEncoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "CommandEncoder.h"
#include "Device.h"
#include "DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Unit/CommandBuffer.h"

namespace Neptune::WebGPU {

    CommandEncoder::CommandEncoder(Context& context, EInfrastructure e)
		: Infrastructure(context, e)
	{}

    void CommandEncoder::Begin()
    {
        NEPTUNE_PROFILE_ZONE
        
        m_CommandEncoder = CreateSP<Unit::CommandEncoder>();
        
        WGPUCommandEncoderDescriptor desc{};
        
        m_CommandEncoder->CreateCommandEncoder(GetContext().Get<IDevice>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(*m_CommandEncoder, ToString())
    }
    
    UP<Unit::CommandBuffer> CommandEncoder::End()
    {
        NEPTUNE_PROFILE_ZONE
        
        auto p = CreateUP<Unit::CommandBuffer>();
        
        WGPUCommandBufferDescriptor desc{};
        
        p->SetHandle(wgpuCommandEncoderFinish(m_CommandEncoder->GetHandle(), &desc));
        
        DEBUGUTILS_SETOBJECTNAME(*p, "CommandBuffer")
        
        m_CommandEncoder.reset();
        
        return p;
    }

}

#endif