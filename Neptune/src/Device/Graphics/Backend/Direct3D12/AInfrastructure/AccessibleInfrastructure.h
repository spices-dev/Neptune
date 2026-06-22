/**
* @file AccessibleInfrastructure.h.
* @brief The AccessibleInfrastructure Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Core.h"
#include "Device/Graphics/Backend/Common/AInfrastructure/AccessibleInfrastructure.h"

namespace Neptune::Direct3D12 {

    /**
    * @brief Enum of Accessible Infrastructure.
    */
    enum class EAccessibleInfrastructure : uint8_t
    {
        Device = 0,             // @brief Device
        CommandQueue,           // @brief CommandQueue
        RTVFormat,              // @brief RTVFormat
        DSVFormat,              // @brief DSVFormat
        SRVDescriptorHeap,      // @brief SRVDescriptorHeap
        SRVCPUHandle,           // @brief SRVCPUHandle
        SRVGPUHandle,           // @brief SRVGPUHandle

        Count
    };

    using ADevice               = Render::Common::AccessibleInfrastructure<ID3D12Device*,                EAccessibleInfrastructure::Device>;
    using ACommandQueue         = Render::Common::AccessibleInfrastructure<ID3D12CommandQueue*,          EAccessibleInfrastructure::CommandQueue>;
    using ARTVFormat            = Render::Common::AccessibleInfrastructure<DXGI_FORMAT,                  EAccessibleInfrastructure::RTVFormat>;
    using ADSVFormat            = Render::Common::AccessibleInfrastructure<DXGI_FORMAT,                  EAccessibleInfrastructure::DSVFormat>;
    using ASRVDescriptorHeap    = Render::Common::AccessibleInfrastructure<ID3D12DescriptorHeap*,        EAccessibleInfrastructure::SRVDescriptorHeap>;
    using ASRVCPUHandle         = Render::Common::AccessibleInfrastructure<D3D12_CPU_DESCRIPTOR_HANDLE,  EAccessibleInfrastructure::SRVCPUHandle>;
    using ASRVGPUHandle         = Render::Common::AccessibleInfrastructure<D3D12_GPU_DESCRIPTOR_HANDLE,  EAccessibleInfrastructure::SRVGPUHandle>;

    using AContext                = Render::Common::AccessibleContext<EAccessibleInfrastructure>;
    
}

#endif