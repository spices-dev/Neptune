/**
* @file DeviceFault.h.
* @brief The DeviceFault Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDeviceFault = IExtension<class DeviceFault, EExtension::DeviceFault>;
    
    class DeviceFault : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        */
        DeviceFault();
        
        /**
        * @brief Destructor Function.
        */
        ~DeviceFault() override = default;

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

        VkPhysicalDeviceFaultFeaturesEXT m_FaultFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FAULT_FEATURES_EXT };    // @brief FaultFeatures.
    };
}

#endif