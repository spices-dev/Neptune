/**
* @file DescriptorBuffer.h.
* @brief The DescriptorBuffer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDescriptorBuffer = IExtension<class DescriptorBuffer, EExtension::DescriptorBuffer>;
    
    class DescriptorBuffer : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit DescriptorBuffer(EExtensionState state = EExtensionState::Core);
        
        /**
        * @brief Destructor Function.
        */
        ~DescriptorBuffer() override = default;
    };
}

#endif