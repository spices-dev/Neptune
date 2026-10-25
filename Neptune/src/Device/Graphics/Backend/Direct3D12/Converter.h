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
	
	/**
	* @brief Convert AttachmentOP to D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE.
	*
	* @param[in] op AttachmentOP.
	*
	* @return Returns D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE.
	*/
	D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE ToD3D12RenderPassBeginAccessType(AttachmentOP op);
	
	/**
	* @brief Convert ECullMode to D3D12_CULL_MODE.
	*
	* @param[in] c ECullMode.
	*
	* @return Returns D3D12_CULL_MODE.
	*/
	D3D12_CULL_MODE ToD3D12CullMode(ECullMode c);
	
	/**
	* @brief Convert ETopology to D3D12_PRIMITIVE_TOPOLOGY_TYPE.
	*
	* @param[in] t ETopology.
	*
	* @return Returns D3D12_PRIMITIVE_TOPOLOGY_TYPE.
	*/
	D3D12_PRIMITIVE_TOPOLOGY_TYPE ToD3D12PrimitiveTopologyType(ETopology t);
}

#endif