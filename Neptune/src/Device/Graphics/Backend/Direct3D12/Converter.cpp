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
	
	D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE ToD3D12RenderPassBeginAccessType(AttachmentOP op)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum AttachmentOP;
		
		switch (op)
		{
			case Clear:                   return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_CLEAR;
			case Load:                    return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported AttachmentOP To D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE.";
				return D3D12_RENDER_PASS_BEGINNING_ACCESS_TYPE_PRESERVE;
			}
		}
	}
	
	D3D12_CULL_MODE ToD3D12CullMode(ECullMode c)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum ECullMode;
		
		switch (c)
		{
			case None:                     return D3D12_CULL_MODE_NONE;
			case Front:                    return D3D12_CULL_MODE_FRONT;
			case Back:                     return D3D12_CULL_MODE_BACK;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported ECullMode To D3D12_CULL_MODE.";
				return D3D12_CULL_MODE_NONE;
			}
		}
	}
	
	D3D12_PRIMITIVE_TOPOLOGY_TYPE ToD3D12PrimitiveTopologyType(ETopology t)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum ETopology;
		
		switch (t)
		{
			case TriangleList:
			case TriangleStrip:                    return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported ETopology To D3D12_PRIMITIVE_TOPOLOGY_TYPE.";
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED;
			}
		}
	}
}

#endif