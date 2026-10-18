/**
* @file DeviceAddressBindingReport.cpp.
* @brief The DeviceAddressBindingReport Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "DeviceAddressBindingReport.h"

namespace Neptune::Vulkan::Extension {

    DeviceAddressBindingReport::DeviceAddressBindingReport(EExtensionState state)
        : Extension(state)
    {
        NEPTUNE_PROFILE_ZONE

        if (IsCoreExtension<decltype(*this)>()) return;

        AddDeviceExtensions(VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_EXTENSION_NAME);
    }

    void DeviceAddressBindingReport::BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter)
    {
        NEPTUNE_PROFILE_ZONE

        LinkToChain(pNext, filter, m_DeviceAddressBindingReportFeatures);
    }
    
    bool DeviceAddressBindingReport::IsFeaturesSatisfied()
    {
        NEPTUNE_PROFILE_ZONE
        
        NEPTUNE_LOG_CORE(I) << "DeviceAddressBindingReport [ reportAddressBinding ] : " << m_DeviceAddressBindingReportFeatures.reportAddressBinding;
        
        if (!m_DeviceAddressBindingReportFeatures.reportAddressBinding)
        {
            return false;
        }

        return true;
    }
    
}

#endif