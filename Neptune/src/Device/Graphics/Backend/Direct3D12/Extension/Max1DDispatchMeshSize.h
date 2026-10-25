/**
* @file Max1DDispatchMeshSize.h.
* @brief The Max1DDispatchMeshSize Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IMax1DDispatchMeshSize = IExtension<class Max1DDispatchMeshSize, EExtension::Max1DDispatchMeshSize>;
    
    class Max1DDispatchMeshSize : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Max1DDispatchMeshSize(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Max1DDispatchMeshSize() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS22 m_Options22{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS22.
    
    };
}

#endif