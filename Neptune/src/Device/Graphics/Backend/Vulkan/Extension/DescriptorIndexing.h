/**
* @file DescriptorIndexing.h.
* @brief The DescriptorIndexing Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDescriptorIndexing = IExtension<class DescriptorIndexing, EExtension::DescriptorIndexing>;

    /**
    * @brief Used In:
    * Descriptor Binding After Update
    */
    class DescriptorIndexing : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 2, 0);
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit DescriptorIndexing(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~DescriptorIndexing() override = default;
        
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