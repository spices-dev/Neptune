/**
* @file BindGroupLayout.cpp.
* @brief The BindGroupLayout Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "BindGroupLayout.h"

namespace Neptune::WebGPU::Unit {

    BindGroupLayout::~BindGroupLayout()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuBindGroupLayoutRelease(m_Handle);
    }

    void BindGroupLayout::CreateBindGroupLayout(WGPUDevice device, const WGPUBindGroupLayoutDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateBindGroupLayout(device, &desc);
    }

    void BindGroupLayout::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuBindGroupLayoutSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif