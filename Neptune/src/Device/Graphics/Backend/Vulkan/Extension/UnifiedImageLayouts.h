/**
* @file UnifiedImageLayouts.h.
* @brief The UnifiedImageLayouts Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IUnifiedImageLayouts = IExtension<class UnifiedImageLayouts, EExtension::UnifiedImageLayouts>;
    
    class UnifiedImageLayouts : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit UnifiedImageLayouts(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~UnifiedImageLayouts() override = default;
        
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
        
        VkPhysicalDeviceUnifiedImageLayoutsFeaturesKHR m_UnifiedImageLayoutsFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_UNIFIED_IMAGE_LAYOUTS_FEATURES_KHR };       // @brief UnifiedImageLayoutsFeatures.
    
    };
}

#endif