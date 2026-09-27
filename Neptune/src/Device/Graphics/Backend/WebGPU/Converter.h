/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core.h"
#include "Asset/SOP/Enum.h"
#include "Device/Graphics/Frontend/Enum.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::WebGPU {
	
	/**
	* @brief Convert AttachmentOP to WGPULoadOp.
	*
	* @param[in] op AttachmentOP.
	*
	* @return Returns WGPULoadOp.
	*/
	WGPULoadOp ToWGPULoadOp(AttachmentOP op);
	
	/**
	* @brief Convert TextureFormat to WGPUTextureFormat.
	*
	* @param[in] f TextureFormat.
	*
	* @return Returns WGPUTextureFormat.
	*/
	WGPUTextureFormat ToWGPUTextureFormat(TextureFormat f);
	
	/**
	* @brief Convert TextureDomain to WGPUTextureDimension.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns WGPUTextureDimension.
	*/
	WGPUTextureDimension ToWGPUTextureDimension(TextureDomain d);
	
	/**
	* @brief Convert TextureDomain to WGPUTextureViewDimension.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns WGPUTextureViewDimension.
	*/
	WGPUTextureViewDimension ToWGPUTextureViewDimension(TextureDomain d);
	
	/**
	* @brief Convert WGPUTextureFormat to TextureFormat.
	*
	* @param[in] f WGPUTextureFormat.
	*
	* @return Returns TextureFormat.
	*/
	TextureFormat ToTextureFormat(WGPUTextureFormat f);
	
	/**
	* @brief Convert ECullMode to WGPUCullMode.
	*
	* @param[in] c ECullMode.
	*
	* @return Returns WGPUCullMode.
	*/
	WGPUCullMode ToWGPUCullMode(ECullMode c);
	
	/**
	* @brief Convert ETopology to WGPUPrimitiveTopology.
	*
	* @param[in] t ETopology.
	*
	* @return Returns WGPUPrimitiveTopology.
	*/
	WGPUPrimitiveTopology ToWGPUPrimitiveTopology(ETopology t);
	
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