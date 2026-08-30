/**
* @file DescriptorHeap.h.
* @brief The DescriptorHeap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IDescriptorHeap = IExtension<class DescriptorHeap, EExtension::DescriptorHeap>;
    
    /**
    * @brief Used In:
    * VK_LAYER_KHRONOS_validation gpu_dump_descriptors
    * VK_LAYER_KHRONOS_validation descriptor_hashing
    */
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

        VkPhysicalDeviceDescriptorHeapFeaturesEXT m_DescriptorHeapFeatures{ VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DESCRIPTOR_HEAP_FEATURES_EXT }; // @briefDescriptorHeapFeatures.
    };
}

#endif