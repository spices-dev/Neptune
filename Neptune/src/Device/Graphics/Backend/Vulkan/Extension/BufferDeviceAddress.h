/**
* @file BufferDeviceAddress.h.
* @brief The BufferDeviceAddress Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Extension {

    using IBufferDeviceAddress = IExtension<class BufferDeviceAddress, EExtension::BufferDeviceAddress>;

    /**
    * @brief Used In:
    * RayTracing
    * Bindless
    */
    class BufferDeviceAddress : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit BufferDeviceAddress(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~BufferDeviceAddress() override = default;
        
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
        
        VkPhysicalDeviceBufferDeviceAddressFeatures m_BufferDeviceAddressFeatures { VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_DEVICE_ADDRESS_FEATURES };  // @brief BufferDeviceAddressFeatures.
    
    };
}

#endif