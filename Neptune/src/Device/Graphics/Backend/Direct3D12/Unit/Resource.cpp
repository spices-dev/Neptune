/**
* @file Resource.cpp.
* @brief The Resource Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Resource.h"

namespace Neptune::Direct3D12::Unit {

	Resource::~Resource()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Resource::CreateCommittedResource(D3D12Device device, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state, D3D12_HEAP_TYPE type)
	{
		NEPTUNE_PROFILE_ZONE

		auto properties = CD3DX12_HEAP_PROPERTIES(type);
		
		DIRECT3D12_CHECK(device->CreateCommittedResource(&properties, D3D12_HEAP_FLAG_NONE, &desc, state, nullptr, IID_PPV_ARGS(&m_Handle)))
	}

	void Resource::CreatePlacedResource(D3D12Device device, D3D12Heap heap, UINT64 offset, const D3D12_RESOURCE_DESC& desc, D3D12_RESOURCE_STATES state)
	{
		NEPTUNE_PROFILE_ZONE

		DIRECT3D12_CHECK(device->CreatePlacedResource(heap, offset, &desc, state, nullptr, IID_PPV_ARGS(&m_Handle)))
	}

}

#endif