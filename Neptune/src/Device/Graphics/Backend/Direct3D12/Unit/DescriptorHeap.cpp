/**
* @file DescriptorHeap.cpp.
* @brief The DescriptorHeap Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "DescriptorHeap.h"

namespace Neptune::Direct3D12::Unit {

	DescriptorHeap::~DescriptorHeap()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void DescriptorHeap::CreateDescriptorHeap(D3D12Device device, const D3D12_DESCRIPTOR_HEAP_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&m_Handle)))
	}

	D3D12_CPU_DESCRIPTOR_HANDLE DescriptorHeap::GetCPUDescriptorHandleForHeapStart() const
	{
		NEPTUNE_PROFILE_ZONE
		
#ifdef _MSC_VER
		
		return m_Handle->GetCPUDescriptorHandleForHeapStart();
		
#else
		
		D3D12_CPU_DESCRIPTOR_HANDLE handle;
		
		m_Handle->GetCPUDescriptorHandleForHeapStart(&handle);
		
		return handle;
		
#endif
		
	}
	
	D3D12_GPU_DESCRIPTOR_HANDLE DescriptorHeap::GetGPUDescriptorHandleForHeapStart() const
	{
		NEPTUNE_PROFILE_ZONE
		
#ifdef _MSC_VER
		
		return m_Handle->GetGPUDescriptorHandleForHeapStart();
		
#else
		
		D3D12_GPU_DESCRIPTOR_HANDLE handle;
		
		m_Handle->GetGPUDescriptorHandleForHeapStart(&handle);

		return handle;
		
#endif
		
	};
	
}

#endif