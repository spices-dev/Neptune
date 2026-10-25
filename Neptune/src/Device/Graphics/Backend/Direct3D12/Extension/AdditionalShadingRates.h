/**
* @file AdditionalShadingRates.h.
* @brief The AdditionalShadingRates Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IAdditionalShadingRates = IExtension<class AdditionalShadingRates, EExtension::AdditionalShadingRates>;
    
    class AdditionalShadingRates : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit AdditionalShadingRates(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~AdditionalShadingRates() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS6 m_Options6{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS6.
    
    };
}

#endif