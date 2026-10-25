/**
* @file AtomicInt64OnGroupShared.h.
* @brief The AtomicInt64OnGroupShared Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IAtomicInt64OnGroupShared = IExtension<class AtomicInt64OnGroupShared, EExtension::AtomicInt64OnGroupShared>;
    
    class AtomicInt64OnGroupShared : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit AtomicInt64OnGroupShared(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~AtomicInt64OnGroupShared() override = default;

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