/**
* @file Blob.cpp.
* @brief The Blob Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Blob.h"

#include <d3dcompiler.h>

namespace Neptune::Direct3D12::Unit {

	Blob::~Blob()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle) return;

		m_Handle->Release();
	}

	void Blob::CreateBlob(const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& desc)
	{
		NEPTUNE_PROFILE_ZONE

		Handle errorBlob = nullptr;

		auto result = D3D12SerializeVersionedRootSignature(&desc, &m_Handle, &errorBlob);

		if (FAILED(result))
		{
			DIRECT3D12_CHECK(result)

			if (!errorBlob) return;

			NEPTUNE_LOG_CORE(E) << errorBlob->GetBufferPointer();
		}
	}
	
	void Blob::CreateBlob(const uint8_t* data, uint32_t size)
	{
		NEPTUNE_PROFILE_ZONE
		
		DIRECT3D12_CHECK(D3DCreateBlob(size, &m_Handle))
		
		std::memcpy(m_Handle->GetBufferPointer(), data, size);
	}

}

#endif