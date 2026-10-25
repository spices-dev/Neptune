/**
* @file Int64ShaderOps.h.
* @brief The Int64ShaderOps Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IInt64ShaderOps = IExtension<class Int64ShaderOps, EExtension::Int64ShaderOps>;
    
    class Int64ShaderOps : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Int64ShaderOps(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Int64ShaderOps() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS1 m_Options1{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS1.
    
    };
}

#endif