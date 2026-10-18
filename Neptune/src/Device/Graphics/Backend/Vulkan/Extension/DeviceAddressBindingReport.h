/**
* @file DeviceAddressBindingReport.h.
* @brief The DeviceAddressBindingReport Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDeviceAddressBindingReport = IExtension<class DeviceAddressBindingReport, EExtension::DeviceAddressBindingReport>;
    
    class DeviceAddressBindingReport : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DeviceAddressBindingReport(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DeviceAddressBindingReport() override = default;
        
        /**
        * @brief Build Device Feature Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Combine Device Features.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied() override;
        
    private:
        
        VkPhysicalDeviceAddressBindingReportFeaturesEXT  m_DeviceAddressBindingReportFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ADDRESS_BINDING_REPORT_FEATURES_EXT };    // @brief DeviceAddressBindingReportFeatures.
    };
}

#endif