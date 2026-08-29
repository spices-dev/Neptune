/**
* @file DescriptorHeap.h.
* @brief The DescriptorHeap Class Definitions and Implementation.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDescriptorHeap = IExtension<class DescriptorHeap, EExtension::DescriptorHeap>;
    
    class DescriptorHeap : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit DescriptorHeap(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~DescriptorHeap() override = default;
    };
}

#endif