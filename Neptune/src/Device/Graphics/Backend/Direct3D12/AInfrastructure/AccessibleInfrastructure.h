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

    using ADevice               = Graphic::Common::AccessibleInfrastructure<ID3D12Device*,                EAccessibleInfrastructure::Device>;
    using ACommandQueue         = Graphic::Common::AccessibleInfrastructure<ID3D12CommandQueue*,          EAccessibleInfrastructure::CommandQueue>;
    using ARTVFormat            = Graphic::Common::AccessibleInfrastructure<DXGI_FORMAT,                  EAccessibleInfrastructure::RTVFormat>;
    using ADSVFormat            = Graphic::Common::AccessibleInfrastructure<DXGI_FORMAT,                  EAccessibleInfrastructure::DSVFormat>;
    using ASRVDescriptorHeap    = Graphic::Common::AccessibleInfrastructure<ID3D12DescriptorHeap*,        EAccessibleInfrastructure::SRVDescriptorHeap>;
    using ASRVCPUHandle         = Graphic::Common::AccessibleInfrastructure<D3D12_CPU_DESCRIPTOR_HANDLE,  EAccessibleInfrastructure::SRVCPUHandle>;
    using ASRVGPUHandle         = Graphic::Common::AccessibleInfrastructure<D3D12_GPU_DESCRIPTOR_HANDLE,  EAccessibleInfrastructure::SRVGPUHandle>;

    using AInfrastructures = std::tuple<
        ADevice::T, 
        ACommandQueue::T,
        ARTVFormat::T,
        ADSVFormat::T,
        ASRVDescriptorHeap::T,
        ASRVCPUHandle::T,
        ASRVGPUHandle::T
    >;
    
    using AContext              = Graphic::Common::AccessibleContext<EAccessibleInfrastructure, AInfrastructures>;
    
}

#endif