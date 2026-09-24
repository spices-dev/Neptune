/**
* @file BindGroup.cpp.
* @brief The BindGroup Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "BindGroup.h"

namespace Neptune::WebGPU::Unit {

    BindGroup::~BindGroup()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuBindGroupRelease(m_Handle);
    }

    void BindGroup::CreateBindGroup(WGPUDevice device, const WGPUBindGroupDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateBindGroup(device, &desc);
    }

    void BindGroup::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuBindGroupSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif