/**
* @file PresentTiming.h.
* @brief The PresentTiming Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IPresentTiming = IExtension<class PresentTiming, EExtension::PresentTiming>;
    
    class PresentTiming : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit PresentTiming(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~PresentTiming() override = default;
        
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
        
        /**
        * @brief Build Device Surface Capabilities Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter SurfaceCapabilities Filter.
        */
        void BuildSurfaceCapabilitiesChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Is Device Surface Capabilities satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsSurfaceCapabilitiesSatisfied() override;
        
    private:
        
        VkPhysicalDevicePresentTimingFeaturesEXT m_PresentTimingFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_TIMING_FEATURES_EXT };    // @brief PresentTimingFeatures;
        VkPhysicalDevicePresentId2FeaturesKHR m_PresentId2Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PRESENT_ID_2_FEATURES_KHR };    // @brief PresentId2Features;
        VkPresentTimingSurfaceCapabilitiesEXT m_PresentTimingSurfaceCapabilities { VK_STRUCTURE_TYPE_PRESENT_TIMING_SURFACE_CAPABILITIES_EXT }; // @brief PresentTimingSurfaceCapabilities;
    };
}

#endif