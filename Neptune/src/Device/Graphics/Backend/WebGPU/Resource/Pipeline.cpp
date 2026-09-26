/**
* @file Pipeline.cpp.
* @brief The Pipeline Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Pipeline.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Device.h"

namespace Neptune::WebGPU::Resource {

    void Pipeline::CreateRenderPipeline(const WGPURenderPipelineDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto pipeline = CreateUP<Unit::RenderPipeline>();
        
        pipeline->CreateRenderPipeline(GetContext().Get<IDevice>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(*pipeline, "RenderPipeline")
        
        m_Pipeline = std::move(pipeline);
    }
    
    void Pipeline::CreateComputePipeline(const WGPUComputePipelineDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE
        
        auto pipeline = CreateUP<Unit::ComputePipeline>();
        
        pipeline->CreateComputePipeline(GetContext().Get<IDevice>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(*pipeline, "ComputePipeline")
        
        m_Pipeline = std::move(pipeline);
    }
    
}

#endif