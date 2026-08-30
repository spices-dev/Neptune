/**
* @file DynamicRenderingLocalRead.h.
* @brief The DynamicRenderingLocalRead Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDynamicRenderingLocalRead = IExtension<class DynamicRenderingLocalRead, EExtension::DynamicRenderingLocalRead>;

    /**
    * @brief Used In:
    * DynamicRendering subpassLoad
    */
    class DynamicRenderingLocalRead : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 4, 0);
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit DynamicRenderingLocalRead(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~DynamicRenderingLocalRead() override = default;

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

        VkPhysicalDeviceDynamicRenderingLocalReadFeatures m_DynamicRenderingLocalReadFeatures{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DYNAMIC_RENDERING_LOCAL_READ_FEATURES }; // @brief DynamicRenderingLocalReadFeatures.
    };
}

#endif