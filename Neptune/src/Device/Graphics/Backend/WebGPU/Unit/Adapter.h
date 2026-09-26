/**
* @file Adapter.h.
* @brief The Adapter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Adapter Class.
	* This class defines the WebGPU::Unit::Adapter behaves.
	*/
	class Adapter : public Unit<WGPUAdapter>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Adapter() = default;

		/**
		* @brief Destructor Function.
		*/
		~Adapter() override;

		/**
		* @brief Create Adapter.
		* 
		* @param[in] instance WGPUInstance.
		* @param[in] options WGPURequestAdapterOptions.
		*/
		void CreateAdapter(WGPUInstance instance, const WGPURequestAdapterOptions& options);

	};
}

#endif