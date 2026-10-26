/**
* @file RootSignature.cpp.
* @brief The RootSignature Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "RootSignature.h"

namespace Neptune::Direct3D12::Unit {

	RootSignature::~RootSignature()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void RootSignature::CreateRootSignature(D3D12Device device, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE
		
		D3DBlob signatureBlob = nullptr;
		D3DBlob errorBlob     = nullptr;
		
		DIRECT3D12_CHECK(D3D12SerializeVersionedRootSignature(&desc, &signatureBlob, &errorBlob))
		
		if (errorBlob)
		{
			NEPTUNE_LOG_CORE(E) << errorBlob->GetBufferPointer();
		}
		
		DIRECT3D12_CHECK(device->CreateRootSignature(0, signatureBlob->GetBufferPointer(), signatureBlob->GetBufferSize(), IID_PPV_ARGS(&m_Handle)))
	}

}

#endif