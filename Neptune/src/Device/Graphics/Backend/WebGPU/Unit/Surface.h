/**
* @file Surface.h.
* @brief The Surface Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Unit.h"

namespace Neptune::WebGPU::Unit {

	/**
	* @brief WebGPU::Unit::Surface Class.
	* This class defines the WebGPU::Unit::Surface behaves.
	*/
	class Surface : public Unit<WGPUSurface>
	{
	public:

		using Handle = Unit::Handle;

	public:

		/**
		* @brief Constructor Function.
		*/
		Surface() = default;

		/**
		* @brief Destructor Function.
		*/
		~Surface() override;

		/**
		* @brief Create Surface.
		*
		* @param[in] instance WGPUInstance.
		* @param[in] desc WGPUSurfaceDescriptor.
		*/
		void CreateSurface(WGPUInstance instance, const WGPUSurfaceDescriptor& desc);
		
		/**
		* @brief Set Unit name.
		* 
		* @param[in] name Unit name.
		*/
		void SetName(const std::string& name) const;
		
	};
}

#endif