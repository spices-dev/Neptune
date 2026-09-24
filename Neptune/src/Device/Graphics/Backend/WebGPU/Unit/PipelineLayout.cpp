/**
* @file PipelineLayout.cpp.
* @brief The PipelineLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "PipelineLayout.h"

namespace Neptune::WebGPU::Unit {

    PipelineLayout::~PipelineLayout()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuPipelineLayoutRelease(m_Handle);
    }

    void PipelineLayout::CreatePipelineLayout(WGPUDevice device, const WGPUPipelineLayoutDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreatePipelineLayout(device, &desc);
    }

    void PipelineLayout::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuPipelineLayoutSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif