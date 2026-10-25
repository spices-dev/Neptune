/**
* @file GPUUploadHeap.h.
* @brief The GPUUploadHeap Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Context.h"

namespace Neptune::Direct3D12::Extension {

    using IGPUUploadHeap = IExtension<class GPUUploadHeap, EExtension::GPUUploadHeap>;
    
    class GPUUploadHeap : public Extension
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] state EExtensionState.
        */
        explicit GPUUploadHeap(EExtensionState state = EExtensionState::Core) : Extension(state) {}
        
        /**
        * @brief Destructor Function.
        */
        ~GPUUploadHeap() override = default;

        /**
        * @brief Combine Device Features.
        * 
        * @param[in] device D3D12Device.
        * 
        * @return Returns true if satisfied.
        */
        bool IsFeaturesSatisfied(D3D12Device device) override;
        
    private:
        
        D3D12_FEATURE_DATA_D3D12_OPTIONS16 m_Options16{};  // @brief D3D12_FEATURE_DATA_D3D12_OPTIONS16.
    
    };
}

#endif