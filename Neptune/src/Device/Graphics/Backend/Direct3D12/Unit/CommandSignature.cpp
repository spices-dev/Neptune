/**
* @file CommandSignature.cpp.
* @brief The CommandSignature Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "CommandSignature.h"

namespace Neptune::Direct3D12::Unit {

    CommandSignature::~CommandSignature()
    {
        NEPTUNE_PROFILE_ZONE

        if (!m_Handle) return;

        m_Handle->Release();
    }

    void CommandSignature::CreateCommandSignature(D3D12Device device, const D3D12_COMMAND_SIGNATURE_DESC& desc)
    {
        NEPTUNE_PROFILE_ZONE

        DIRECT3D12_CHECK(device->CreateCommandSignature(&desc, nullptr, IID_PPV_ARGS(&m_Handle)))
    }

}

#endif