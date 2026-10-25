/**
* @file ShaderResourceView.h.
* @brief The ShaderResourceView Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

    /**
    * @brief Direct3D12::Unit::ShaderResourceView Class.
    * This class defines the Direct3D12::Unit::ShaderResourceView behaves.
    */
    class ShaderResourceView : public Unit<int>
    {
    public:

        using Handle = Unit::Handle;

    public:

        /**
        * @brief Constructor Function.
        */
        ShaderResourceView() = default;

        /**
        * @brief Destructor Function.
        */
        ~ShaderResourceView() override = default;

        /**
        * @brief Create ShaderResourceView.
        *
        * @param[in] device D3D12Device.
        * @param[in] resource D3D12Resource.
        * @param[in] desc D3D12_SHADER_RESOURCE_VIEW_DESC.
        * @param[in] heap D3D12DescriptorHeap.
        * @param[in] alignment D3D12DescriptorHeap Alignment.
        */
        void CreateShaderResourceView(D3D12Device device, D3D12Resource resource, const D3D12_SHADER_RESOURCE_VIEW_DESC& desc, D3D12DescriptorHeap heap, uint32_t alignment);

    };
}

#endif