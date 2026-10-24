/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Converter.h"

namespace Neptune::Direct3D12 {

	TextureFormat ToTextureFormat(DXGI_FORMAT f)
	{
		NEPTUNE_PROFILE_ZONE

		switch (f)
		{
			case DXGI_FORMAT_R8G8B8A8_UNORM:                  return TextureFormat::RGBA8_UNORM;
			case DXGI_FORMAT_R8G8B8A8_UINT:                   return TextureFormat::RGBA8_UINT;
			case DXGI_FORMAT_R16G16B16A16_FLOAT:              return TextureFormat::RGBA16_SFLOAT;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported DXGI_FORMAT To Texture Format.";
				return TextureFormat::RGBA8_UNORM;
			}
		}
	}
}

#endif