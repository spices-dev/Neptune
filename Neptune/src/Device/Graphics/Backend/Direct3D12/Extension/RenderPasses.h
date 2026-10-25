/**
* @file RenderPasses.h.
* @brief The RenderPasses Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IRenderPasses = IExtension<class RenderPasses, EExtension::RenderPasses>;
    
    class RenderPasses : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit RenderPasses(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~RenderPasses() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS5  m_Options5{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS5.
        D3D12_FEATURE_DATA_D3D12_OPTIONS18 m_Options18{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS18.
    
    };
}

#endif