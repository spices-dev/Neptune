/**
* @file ToolingInfo.h.
* @brief The ToolingInfo Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IToolingInfo = IExtension<class ToolingInfo, EExtension::ToolingInfo>;
    
    class ToolingInfo : public Extension
    {
    public:
        
        static constexpr uint32_t CoreVersion = VK_MAKE_VERSION(1, 3, 0);
    
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit ToolingInfo(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~ToolingInfo() override = default;
    
    };
}

#endif