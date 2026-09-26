/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core.h"
#include "Device/Graphics/Frontend/Enum.h"

namespace Neptune::WebGPU {
	
	/**
	* @brief Convert Graphic::EBufferUsage to WGPUBufferUsage.
	*
	* @param[in] u Graphic::EBufferUsage.
	*
	* @return Returns WGPUBufferUsage.
	*/
	WGPUBufferUsage ToWGPUBufferUsage(Graphic::EBufferUsage u);
	
	/**
	* @brief Convert WGPUBackendType to std::string.
	*
	* @param[in] t WGPUBackendType.
	*
	* @return Returns std::string.
	*/
	std::string ToString(WGPUBackendType t);
	
	/**
	* @brief Convert WGPUAdapterType to std::string.
	*
	* @param[in] t WGPUAdapterType.
	*
	* @return Returns std::string.
	*/
	std::string ToString(WGPUAdapterType t);

}

#endif