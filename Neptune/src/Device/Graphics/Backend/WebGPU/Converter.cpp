/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Converter.h"

namespace Neptune::WebGPU {
	
	WGPULoadOp ToWGPULoadOp(AttachmentOP op)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum AttachmentOP;
		
		switch (op)
		{
			case Clear:                      return WGPULoadOp_Clear;
			case Load:                       return WGPULoadOp_Load;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported AttachmentOP To WGPULoadOp.";
				return WGPULoadOp_Undefined;
			}
		}
	}
	
	WGPUTextureFormat ToWGPUTextureFormat(TextureFormat f)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum TextureFormat;
		
		switch (f)
		{
			case RGBA8_UNORM:                      return WGPUTextureFormat_RGBA8Unorm;
			case RGBA16_SFLOAT:                    return WGPUTextureFormat_RGBA16Float;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported TextureFormat To WGPUTextureFormat.";
				return WGPUTextureFormat_Undefined;
			}
		}
	}
	
	WGPUTextureDimension ToWGPUTextureDimension(TextureDomain d)
	{
		using enum TextureDomain;
		
		switch (d)
		{
			case Texture1D:                      return WGPUTextureDimension_1D;
			case Texture2D:                      return WGPUTextureDimension_2D;
			case Texture3D:                      return WGPUTextureDimension_3D;
			case Texture1DArray:                 return WGPUTextureDimension_1D;
			case Texture2DArray:                 return WGPUTextureDimension_2D;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported TextureDomain To WGPUTextureDimension.";
				return WGPUTextureDimension_Undefined;
			}
		}
	}
	
	WGPUTextureViewDimension ToWGPUTextureViewDimension(TextureDomain d)
	{
		using enum TextureDomain;
		
		switch (d)
		{
			case Texture1D:                      return WGPUTextureViewDimension_1D;
			case Texture2D:                      return WGPUTextureViewDimension_2D;
			case Texture3D:                      return WGPUTextureViewDimension_3D;
			case Texture2DArray:                 return WGPUTextureViewDimension_2DArray;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported TextureDomain To WGPUTextureViewDimension.";
				return WGPUTextureViewDimension_Undefined;
			}
		}
	}
	
	TextureFormat ToTextureFormat(WGPUTextureFormat f)
	{
		NEPTUNE_PROFILE_ZONE
		
		switch (f)
		{
			case WGPUTextureFormat_RGBA8Unorm:                  return TextureFormat::RGBA8_UNORM;
			case WGPUTextureFormat_RGBA16Float:                 return TextureFormat::RGBA16_SFLOAT;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported WGPUTextureFormat To TextureFormat.";
				return TextureFormat::Count;
			}
		}
	}
	
	WGPUCullMode ToWGPUCullMode(ECullMode c)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum ECullMode;
		
		switch (c)
		{
			case None:                  return WGPUCullMode_None;
			case Front:                 return WGPUCullMode_Front;
			case Back:                  return WGPUCullMode_Back;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported ECullMode To WGPUCullMode.";
				return WGPUCullMode_Undefined;
			}
		}
	}
	
	WGPUPrimitiveTopology ToWGPUPrimitiveTopology(ETopology t)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum ETopology;
		
		switch (t)
		{
			case TriangleList:                  return WGPUPrimitiveTopology_TriangleList;
			case TriangleStrip:                 return WGPUPrimitiveTopology_TriangleStrip;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported ETopology To WGPUPrimitiveTopology.";
				return WGPUPrimitiveTopology_Undefined;
			}
		}
	}
	
	WGPUBufferUsage ToWGPUBufferUsage(Graphic::EBufferUsage u)
	{
		NEPTUNE_PROFILE_ZONE
		
		using enum Graphic::EBufferUsage;
		
		switch (u)
		{
			case None:                   return WGPUBufferUsage_None;
			case Vertex:                 return WGPUBufferUsage_Vertex;
			case Index:                  return WGPUBufferUsage_Index;
			case Indirect:               return WGPUBufferUsage_Indirect;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported EBufferUsage To WGPUBufferUsage.";
				return 0;
			}
		}
	}
	
	std::string ToString(WGPUBackendType t)
	{
		NEPTUNE_PROFILE_ZONE
		
		switch (t)
		{
			case WGPUBackendType_Null:                return "Null";
			case WGPUBackendType_WebGPU:              return "WebGPU";
			case WGPUBackendType_D3D11:               return "D3D11";
			case WGPUBackendType_D3D12:               return "D3D12";
			case WGPUBackendType_Metal:               return "Metal";
			case WGPUBackendType_Vulkan:              return "Vulkan";
			case WGPUBackendType_OpenGL:              return "OpenGL";
			case WGPUBackendType_OpenGLES:            return "OpenGLES";
			default:                                  return "NonNamed";
		}
	}
	
	std::string ToString(WGPUAdapterType t)
	{
		NEPTUNE_PROFILE_ZONE
		
		switch (t)
		{
			case WGPUAdapterType_IntegratedGPU:    return "Integrated";
			case WGPUAdapterType_DiscreteGPU:      return "Discrete";
			case WGPUAdapterType_CPU:              return "CPU";
			default:                               return "NonNamed";
		}
	}
}

#endif