/**
* @file SwapChain.cpp.
* @brief The SwapChain Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#if defined(NP_GRAPHICS_DIRECT3D11) && defined(NP_WINDOW_SDL)

#include "SwapChain.h"

#include <SDL3/SDL.h>
#include <windows.h>

namespace Neptune::Direct3D11::SDL {

    SwapChain::SwapChain(Context& context, EInfrastructure e, uint32_t count, void* window)
        : Direct3D11::SwapChain(context, e)
    {
		NEPTUNE_PROFILE_ZONE

        Create(count, window);
    }

	void SwapChain::Create(uint32_t count, void* window)
    {
        NEPTUNE_PROFILE_ZONE

        auto sdlWindow = static_cast<SDL_Window*>(window);

        int w; 
        int h;

        SDL_GetWindowSizeInPixels(sdlWindow, &w, &h);

		DXGI_SWAP_CHAIN_DESC1                desc{};
        desc.Width                         = w;
        desc.Height                        = h;
        
        Direct3D11::SwapChain::Create(desc, count, static_cast<HWND>(SDL_GetPointerProperty(SDL_GetWindowProperties(sdlWindow), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr)));
    }

}

#endif