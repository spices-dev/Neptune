/**
* @file SubgroupSizeControl.h.
* @brief The SubgroupSizeControl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ISubgroupSizeControl = IExtension<class SubgroupSizeControl, EExtension::SubgroupSizeControl>;
    
    class SubgroupSizeControl : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 3, 0);
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit SubgroupSizeControl(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~SubgroupSizeControl() override = default;
        
        /**
        * @brief Build Device Feature Chain.
        *
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildFeatureChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Build Device Property Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;
        
        /**
        * @brief Combine Device Features.
        *
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied() override;

        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;
        
    private:

        VkPhysicalDeviceVulkan13Features m_Vulkan13Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };  // @brief Vulkan13Features.
        
        VkPhysicalDeviceSubgroupSizeControlProperties m_SubgroupSizeControlProperties{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_SIZE_CONTROL_PROPERTIES }; // @brief SubgroupSizeControlProperties.
    
    };
}

#endif