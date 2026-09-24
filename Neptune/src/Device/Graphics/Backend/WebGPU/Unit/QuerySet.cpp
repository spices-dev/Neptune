/**
* @file QuerySet.cpp.
* @brief The QuerySet Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Adapter.h"
#include "QuerySet.h"

namespace Neptune::WebGPU::Unit {

    QuerySet::~QuerySet()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        wgpuQuerySetRelease(m_Handle);
    }

    void QuerySet::CreateQuerySet(WGPUDevice device, const WGPUQuerySetDescriptor& desc)
    {
        NEPTUNE_PROFILE_ZONE

        m_Handle = wgpuDeviceCreateQuerySet(device, &desc);
    }

    void QuerySet::SetName(const std::string& name) const
    {
        NEPTUNE_PROFILE_ZONE
		
        wgpuQuerySetSetLabel(m_Handle, { name.c_str(), name.size() });
    }
    
}

#endif