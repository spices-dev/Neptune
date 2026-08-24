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
        */
        SwapChain();
        
        /**
        * @brief Destructor Function.
        */
        ~SwapChain() override = default;
    };
}

#endif