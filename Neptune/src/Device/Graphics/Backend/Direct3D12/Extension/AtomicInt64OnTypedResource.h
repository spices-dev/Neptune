/**
* @file AtomicInt64OnTypedResource.h.
* @brief The AtomicInt64OnTypedResource Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IAtomicInt64OnTypedResource = IExtension<class AtomicInt64OnTypedResource, EExtension::AtomicInt64OnTypedResource>;
    
    class AtomicInt64OnTypedResource : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit AtomicInt64OnTypedResource(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~AtomicInt64OnTypedResource() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS9 m_Options9{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS9.
    
    };
}

#endif