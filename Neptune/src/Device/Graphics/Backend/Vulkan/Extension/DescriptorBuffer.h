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
    
    /**
    * @brief Used In:
    * Not in VK_LAYER_KHRONOS_validation syncval_shader_accesses_heuristic
    * VK_LAYER_KHRONOS_validation gpu_dump_descriptors
    * VK_LAYER_KHRONOS_validation descriptor_hashing
    */
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