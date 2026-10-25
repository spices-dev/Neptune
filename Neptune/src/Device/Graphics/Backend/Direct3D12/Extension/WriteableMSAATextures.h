/**
* @file WriteableMSAATextures.h.
* @brief The WriteableMSAATextures Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IWriteableMSAATextures = IExtension<class WriteableMSAATextures, EExtension::WriteableMSAATextures>;
    
    class WriteableMSAATextures : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit WriteableMSAATextures(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~WriteableMSAATextures() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS14 m_Options14{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS14.
    
    };
}

#endif