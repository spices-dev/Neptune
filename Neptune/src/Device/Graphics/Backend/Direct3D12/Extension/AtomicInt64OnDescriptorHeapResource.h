/**
* @file AtomicInt64OnDescriptorHeapResource.h.
* @brief The AtomicInt64OnDescriptorHeapResource Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IAtomicInt64OnDescriptorHeapResource = IExtension<class AtomicInt64OnDescriptorHeapResource, EExtension::AtomicInt64OnDescriptorHeapResource>;
    
    class AtomicInt64OnDescriptorHeapResource : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit AtomicInt64OnDescriptorHeapResource(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~AtomicInt64OnDescriptorHeapResource() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS11 m_Options11{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS11.
    
    };
}

#endif