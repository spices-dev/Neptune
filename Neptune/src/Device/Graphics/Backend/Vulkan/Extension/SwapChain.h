/**
* @file SwapChain.h.
* @brief The SwapChain Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using ISwapChain = IExtension<class SwapChain, EExtension::SwapChain>;
    
    class SwapChain : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * @param[in] windowExtensions Window Extensions.
        */
        SwapChain(const std::vector<const char*>& windowExtensions = {});
        
        /**
        * @brief Destructor Function.
        */
        ~SwapChain() override = default;
    };
}

#endif