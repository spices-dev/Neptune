/**
* @file DynamicRendering.h.
* @brief The DynamicRendering Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDynamicRendering = IExtension<class DynamicRendering, EExtension::DynamicRendering>;

    /**
    * @brief Used In:
    * Seperate Pipeline State
    * VK_LAYER_LUNARG_crash_diagnostic sync_after_commands
    */
    class DynamicRendering : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DynamicRendering(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DynamicRendering() override = default;

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

        VkPhysicalDeviceDynamicRenderingFeatures m_DynamicRenderingFeatures{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_FEATURES }; // @brief DynamicRenderingFeatures.
    };
}

#endif