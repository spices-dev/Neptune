/**
* @file PageableDeviceLocalMemory.h.
* @brief The PageableDeviceLocalMemory Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IPageableDeviceLocalMemory = IExtension<class PageableDeviceLocalMemory, EExtension::PageableDeviceLocalMemory>;

    class PageableDeviceLocalMemory : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit PageableDeviceLocalMemory(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~PageableDeviceLocalMemory() override = default;

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

        VkPhysicalDevicePageableDeviceLocalMemoryFeaturesEXT m_PageableDeviceLocalMemoryFeatures{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PAGEABLE_DEVICE_LOCAL_MEMORY_FEATURES_EXT }; // @brief PageableDeviceLocalMemoryFeatures.
    };
}

#endif