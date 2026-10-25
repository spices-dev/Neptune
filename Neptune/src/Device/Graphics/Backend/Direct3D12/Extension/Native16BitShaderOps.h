/**
* @file Native16BitShaderOps.h.
* @brief The Native16BitShaderOps Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using INative16BitShaderOps = IExtension<class Native16BitShaderOps, EExtension::Native16BitShaderOps>;
    
    class Native16BitShaderOps : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit Native16BitShaderOps(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~Native16BitShaderOps() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS4 m_Options4{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS4.
    
    };
}

#endif