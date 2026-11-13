/**
* @file Synchronization2.h.
* @brief The Synchronization2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ISynchronization2 = IExtension<class Synchronization2, EExtension::Synchronization2>;
    
    class Synchronization2 : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 3, 0);
        
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Synchronization2(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~Synchronization2() override = default;
        
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
        
        VkPhysicalDeviceVulkan13Features m_Vulkan13Features { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES };  // @brief Vulkan13Features.
    
    };
}

#endif