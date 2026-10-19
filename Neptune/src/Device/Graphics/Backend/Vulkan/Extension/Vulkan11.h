/**
* @file Vulkan11.h.
* @brief The Vulkan11 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IVulkan11 = IExtension<class Vulkan11, EExtension::Vulkan11>;

    /**
    * @brief Used In:
    * Spir-V SV_VulkanVertexID -> SV_VertexID
    */
    class Vulkan11 : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Vulkan11(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Vulkan11() override = default;
        
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
        
        VkPhysicalDeviceVulkan11Features m_Vulkan11Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_1_FEATURES };  // @brief Vulkan11Features.
    
    };
}

#endif