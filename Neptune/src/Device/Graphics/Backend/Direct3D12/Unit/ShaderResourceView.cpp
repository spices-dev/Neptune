/**
* @file ShaderResourceView.cpp.
* @brief The ShaderResourceView Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "ShaderResourceView.h"

namespace Neptune::Direct3D12::Unit {

    void ShaderResourceView::CreateShaderResourceView(D3D12Device device, D3D12Resource resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& desc, D3D12DescriptorHeap heap, uint32_t alignment)
    {
        NEPTUNE_PROFILE_ZONE
        
        CD3DX12_CPU_DESCRIPTOR_HANDLE handle(heap->GetCPUDescriptorHandleForHeapStart());
        
        handle.Offset(m_Handle, alignment);
        
        device->CreateShaderResourceView(resource, &desc, handle);
    }

}

#endif