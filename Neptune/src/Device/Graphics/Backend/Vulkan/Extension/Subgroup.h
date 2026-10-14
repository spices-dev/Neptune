/**
* @file Subgroup.h.
* @brief The Subgroup Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ISubgroup = IExtension<class Subgroup, EExtension::Subgroup>;
    
    class Subgroup : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 1, 0);
    
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Subgroup(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Subgroup() override = default;
        
        /**
        * @brief Build Device Property Chain.
        * 
        * @param[in,out] pNext pNext Chain.
        * @param[in] filter Feature Filter.
        */
        void BuildPropertyChain(void**& pNext, const std::function<bool(VkStructureType)>& filter) override;

        /**
        * @brief Is Device Properties satisfied.
        * 
        * @return Returns true if satisfied.
        */
        bool IsPropertiesSatisfied() override;

    private:

        VkPhysicalDeviceSubgroupProperties m_SubgroupProperties{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_SUBGROUP_PROPERTIES }; // @brief SubgroupProperties.
    
    };
}

#endif