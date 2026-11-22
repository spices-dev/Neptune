/**
* @file RenderBackendInterface.cpp.
* @brief The Interface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_SDL

#include "RenderBackendInterface.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

namespace Neptune::SDL {

	UP<APIInterface> CreateInterface(RenderBackendEnum backend)
	{
		NEPTUNE_PROFILE_ZONE

		switch (backend)
		{
#ifdef NP_GRAPHICS_OPENGL
			case RenderBackendEnum::OpenGL:     return CreateUP<OpenGLInterface>();
#endif
			
#ifdef NP_GRAPHICS_VULKAN
			case RenderBackendEnum::Vulkan:     return CreateUP<VulkanInterface>();
#endif
			
#ifdef NP_GRAPHICS_DIRECT3D11
			case RenderBackendEnum::Direct3D11: return CreateUP<Direct3D11Interface>();
#endif
			
#ifdef NP_GRAPHICS_DIRECT3D12
			case RenderBackendEnum::Direct3D12: return CreateUP<Direct3D12Interface>();
#endif
			
#ifdef NP_GRAPHICS_METAL
		case RenderBackendEnum::Metal: return CreateUP<MetalInterface>();
#endif
			
			default:
			{
				NEPTUNE_LOG_CORE(C) << "Not supported RenderBackend in SDL Configuration.";
				return nullptr;
			}
		}
	}

#ifdef NP_GRAPHICS_OPENGL
	
	uint64_t OpenGLInterface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		// Set OpenGL Version 4.6.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#ifdef NEPTUNE_DEBUG
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

#endif
		
		SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
		
		return SDL_WINDOW_OPENGL;
	}

	void OpenGLInterface::APILoad(SDL_Window* handle) const
	{
		NEPTUNE_PROFILE_ZONE

		auto ctx = SDL_GL_CreateContext(handle);
		
		if (!SDL_GL_MakeCurrent(handle, ctx))
		{
			NEPTUNE_LOG_CORE(C) << "SDL APILoad Failed: " << SDL_GetError();
		}
	}

	void OpenGLInterface::APIUnLoad() const
	{
		NEPTUNE_PROFILE_ZONE
		
		if (!SDL_GL_DestroyContext(SDL_GL_GetCurrentContext()))
		{
			NEPTUNE_LOG_CORE(C) << "SDL APIUnLoad Failed: " << SDL_GetError();
		}
	}

	uint64_t VulkanInterface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		return SDL_WINDOW_VULKAN;
	}

#endif
	
#ifdef NP_GRAPHICS_VULKAN
	
	std::vector<const char*> VulkanInterface::Extension() const
	{
		NEPTUNE_PROFILE_ZONE
		
		Uint32 extCount = 0;
		
		const char* const* sdlExts = SDL_Vulkan_GetInstanceExtensions(&extCount);
		
		return std::vector(sdlExts, sdlExts + extCount);
	}
	
#endif
	
#ifdef NP_GRAPHICS_DIRECT3D11

	uint64_t Direct3D11Interface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		return 0;
	}
	
#endif
	
#ifdef NP_GRAPHICS_DIRECT3D12
	
	uint64_t Direct3D12Interface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		return 0;
	}

#endif
	
#ifdef NP_GRAPHICS_METAL
	
	uint64_t MetalInterface::Hint() const
	{
		NEPTUNE_PROFILE_ZONE

		return SDL_WINDOW_METAL;
	}

#endif
	
}

#endif