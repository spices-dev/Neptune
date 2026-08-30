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

        VkPhysicalDeviceDescriptorBufferFeaturesEXT m_DescriptorBufferFeatures{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_BUFFER_FEATURES_EXT }; // @briefDescriptorBufferFeatures.
    };
}

#endif