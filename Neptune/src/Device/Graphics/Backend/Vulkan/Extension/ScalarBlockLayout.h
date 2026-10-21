/**
* @file ScalarBlockLayout.h.
* @brief The ScalarBlockLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IScalarBlockLayout = IExtension<class ScalarBlockLayout, EExtension::ScalarBlockLayout>;
    
    class ScalarBlockLayout : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ScalarBlockLayout(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ScalarBlockLayout() override = default;
        
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

        VkPhysicalDeviceVulkan12Features m_Vulkan12Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES };  // @brief Vulkan12Features.
    
    };
}

#endif