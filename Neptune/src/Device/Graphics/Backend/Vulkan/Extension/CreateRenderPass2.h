/**
* @file CreateRenderPass2.h.
* @brief The CreateRenderPass2 Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ICreateRenderPass2 = IExtension<class CreateRenderPass2, EExtension::CreateRenderPass2>;

    class CreateRenderPass2 : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 2, 0);
        
    public:

        /**
        * @brief Constructor Function.
        *
        * @param[in] state EExtensionState.
        */
        explicit CreateRenderPass2(EExtensionState state = EExtensionState::Core);

        /**
        * @brief Destructor Function.
        */
        ~CreateRenderPass2() override = default;
    };
}

#endif