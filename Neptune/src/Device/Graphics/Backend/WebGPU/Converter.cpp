/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_WEBGPU

#include "Converter.h"

namespace Neptune::WebGPU {
	
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