/**
* @file FrameBoundary.h.
* @brief The FrameBoundary Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IFrameBoundary = IExtension<class FrameBoundary, EExtension::FrameBoundary>;
    
    class FrameBoundary : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit FrameBoundary(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~FrameBoundary() override = default;
        
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
        
        VkPhysicalDeviceFrameBoundaryFeaturesEXT m_FrameBoundaryFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAME_BOUNDARY_FEATURES_EXT };  // @brief FrameBoundaryFeatures.
    };
}

#endif