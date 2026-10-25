/**
* @file UnrestrictedBufferTextureCopyPitch.h.
* @brief The UnrestrictedBufferTextureCopyPitch Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IUnrestrictedBufferTextureCopyPitch = IExtension<class UnrestrictedBufferTextureCopyPitch, EExtension::UnrestrictedBufferTextureCopyPitch>;
    
    class UnrestrictedBufferTextureCopyPitch : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit UnrestrictedBufferTextureCopyPitch(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~UnrestrictedBufferTextureCopyPitch() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS13 m_Options13{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS13.
    
    };
}

#endif