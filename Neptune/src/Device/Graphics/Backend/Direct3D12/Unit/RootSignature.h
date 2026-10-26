/**
* @file RootSignature.h.
* @brief The RootSignature Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::Direct3D12::Unit {

	/**
	* @brief Direct3D12::Unit::RootSignature Class.
	* This class defines the Direct3D12::Unit::RootSignature behaves.
	*/
	class RootSignature : public Unit<D3D12RootSignature>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		RootSignature() = default;

		/**
		* @brief Destructor Function.
		*/
		~RootSignature() override;

		/**
		* @brief Create RootSignature.
		*
		* @param[in] device D3D12Device.
		* @param[in] desc D3D12_VERSIONED_ROOT_SIGNATURE_DESC.
		*/
		void CreateRootSignature(D3D12Device device, const D3D12_VERSIONED_ROOT_SIGNATURE_DESC& desc);

	};
}

#endif