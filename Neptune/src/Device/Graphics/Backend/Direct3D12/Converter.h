/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core.h"
#include "Resource/Texture/RenderTarget.h"
#include "Asset/SOP/Enum.h"
#include "Resource/Shader/Shader.h"
#include "Device/Graphics/Frontend/Memory.h"

namespace Neptune::Direct3D12 {
	
	/**
	* @brief Convert DXGI_FORMAT to TextureFormat.
	*
	* @param[in] f DXGI_FORMAT.
	*
	* @return Returns TextureFormat.
	*/
	TextureFormat ToTextureFormat(DXGI_FORMAT f);

	/**
	* @brief Convert TextureDomain to D3D12_RESOURCE_DIMENSION.
	*
	* @param[in] d TextureDomain.
	*
	* @return Returns D3D12_RESOURCE_DIMENSION.
	*/
	D3D12_RESOURCE_DIMENSION ToD3D12ResourceDimension(TextureDomain d);

	/**
	* @brief Convert TextureFormat to DXGI_FORMAT.
	*
	* @param[in] f TextureFormat.
	*
	* @return Returns DXGI_FORMAT.
	*/
	DXGI_FORMAT ToDXGIFormat(TextureFormat f);
	
	/**
	* @brief Convert EImageUsage to D3D12_RESOURCE_FLAGS.
	*
	* @param[in] set Container::BitSet<Graphic::EImageUsage>.
	*
	* @return Returns D3D12_RESOURCE_FLAGS.
	*/
	D3D12_RESOURCE_FLAGS ToD3D12ResourceFlags(const Container::BitSet<Graphic::EImageUsage>& set);
}

#endif