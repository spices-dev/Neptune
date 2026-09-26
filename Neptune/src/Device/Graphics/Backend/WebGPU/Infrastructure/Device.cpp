/**
* @file Device.cpp.
* @brief The Device Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Device.h"
#include "Instance.h"
#include "Adapter.h"
#include "DebugUtilsObject.h"

namespace Neptune::WebGPU {

    Device::Device(Context& context, EInfrastructure e)
        : Infrastructure(context, e)
    {
        NEPTUNE_PROFILE_ZONE

        Create();
    }

    void Device::Create()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUDeviceLostCallbackInfo                  deviceLostInfo{};
        deviceLostInfo.mode                       = WGPUCallbackMode_WaitAnyOnly;
        deviceLostInfo.callback                   = DeviceLostCallback;
                                                  
        WGPUUncapturedErrorCallbackInfo             errorInfo{};
        errorInfo.callback                        = UncapturedErrorCallback;
        
        WGPUDeviceDescriptor                        desc{};
        desc.deviceLostCallbackInfo               = deviceLostInfo;
        desc.uncapturedErrorCallbackInfo          = errorInfo;
        desc.requiredFeatureCount                 = GetContext().Get<IAdapter>()->GetFeatures().size();
        desc.requiredFeatures                     = GetContext().Get<IAdapter>()->GetFeatures().data();
        desc.requiredLimits                       = &GetContext().Get<IAdapter>()->GetLimits();
            
        m_Device.CreateDevice(GetContext().Get<IInstance>()->Handle(), GetContext().Get<IAdapter>()->Handle(), desc);
        
        DEBUGUTILS_SETOBJECTNAME(m_Device, ToString())
    }

    void Device::GetLostFuture()
    {
        NEPTUNE_PROFILE_ZONE

        wgpuDeviceGetLostFuture(m_Device.GetHandle());
    }

    void Device::PopErrorScope()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUPopErrorScopeCallbackInfo info{};

        wgpuDevicePopErrorScope(m_Device.GetHandle(), info);
    }

    void Device::PushErrorScope()
    {
        NEPTUNE_PROFILE_ZONE

        WGPUErrorFilter filter{};

        wgpuDevicePushErrorScope(m_Device.GetHandle(), filter);
    }

}

#endif