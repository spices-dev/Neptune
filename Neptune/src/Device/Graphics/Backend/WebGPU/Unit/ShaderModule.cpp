/**
* @file ShaderModule.cpp.
* @brief The ShaderModule Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "ShaderModule.h"

namespace Neptune::WebGPU::Unit {

    ShaderModule::~ShaderModule()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuShaderModuleRelease(m_Handle);
    }

    void ShaderModule::CreateShaderModule(WGPUDevice device, const WGPUShaderModuleDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateShaderModule(device, &desc);
    }

    void ShaderModule::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuShaderModuleSetLabel(m_Handle, { name.c_str(), name.size() });
    }
}

#endif