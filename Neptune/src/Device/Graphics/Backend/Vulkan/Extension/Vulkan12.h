/**
* @file Vulkan12.h.
* @brief The Vulkan12 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVulkan12 = IExtension<class Vulkan12, EExtension::Vulkan12>;

    /**
    * @brief Used In:
    * Spir-V float16
    */
    class Vulkan12 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Vulkan12(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Vulkan12() override = default;
        
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