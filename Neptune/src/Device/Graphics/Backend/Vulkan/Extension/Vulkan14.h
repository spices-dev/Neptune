/**
* @file Vulkan14.h.
* @brief The Vulkan14 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVulkan14 = IExtension<class Vulkan14, EExtension::Vulkan14>;
    
    class Vulkan14 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Vulkan14(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Vulkan14() override = default;
        
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
        
        VkPhysicalDeviceVulkan14Features m_Vulkan14Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_4_FEATURES };  // @brief Vulkan14Features.
    
    };
}

#endif