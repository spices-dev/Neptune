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

#include <vk_mem_alloc.h>

namespace Neptune::Direct3D12 {
	
	/**
	* @brief Convert DXGI_FORMAT to TextureFormat.
	*
	* @param[in] f DXGI_FORMAT.
	*
	* @return Returns TextureFormat.
	*/
	TextureFormat ToTextureFormat(DXGI_FORMAT f);

}

#endif