/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core.h"

namespace Neptune::WebGPU {
	
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