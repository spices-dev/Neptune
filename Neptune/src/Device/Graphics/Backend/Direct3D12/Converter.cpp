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
	
	D3D12_RESOURCE_DIMENSION ToD3D12ResourceDimension(TextureDomain d)
	{
		NEPTUNE_PROFILE_ZONE

		using enum TextureDomain;
		
		switch (d)
		{
			case Texture1D:                   return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
			case Texture2D:                   return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			case Texture3D:                   return D3D12_RESOURCE_DIMENSION_TEXTURE3D;
			case Texture1DArray:              return D3D12_RESOURCE_DIMENSION_TEXTURE1D;
			case Texture2DArray:              return D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported TextureDomain To D3D12_RESOURCE_DIMENSION.";
				return D3D12_RESOURCE_DIMENSION_UNKNOWN;
			}
		}
	}
	
	DXGI_FORMAT ToDXGIFormat(TextureFormat f)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum TextureFormat;
		
		switch (f)
		{
		case RGBA8_UNORM:                   return DXGI_FORMAT_R8G8B8A8_UNORM;
		case RGBA8_UINT:                    return DXGI_FORMAT_R8G8B8A8_UINT;
		case RGBA16_SFLOAT:                 return DXGI_FORMAT_R16G16B16A16_FLOAT;
		default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported TextureFormat To DXGI_FORMAT.";
				return DXGI_FORMAT_R8G8B8A8_UNORM;
			}
		}
	}
	
	D3D12_RESOURCE_FLAGS ToD3D12ResourceFlags(const Container::BitSet<Graphic::EImageUsage>& set)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum Graphic::EImageUsage;
		
		D3D12_RESOURCE_FLAGS flag = D3D12_RESOURCE_FLAG_NONE;
		
		if (set.Test(ColorAttachment)) flag |= D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
		if (set.Test(Storage))         flag |= D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;
		
		return flag;
	}
}

#endif