/**
* @file RHICapturerImpl.cpp.
* @brief The RHICapturerImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_RHICAPTURER_RENDERDOC

#include "RHICapturerImpl.h"

#include <renderdoc_app.h>
#include <Windows.h>

namespace {

	constexpr char dll_path[] = "renderdoc.dll";    // @brief RenderDoc DLL Path.
	
	RENDERDOC_API_1_7_0* s_Api = nullptr;           // @brief RenderDoc api.
	HWND s_Window = NULL;                           // @brief RenderDoc captured window.
	
}

void Initialize()
{
	NEPTUNE_PROFILE_ZONE

	HMODULE mod = GetModuleHandleA(dll_path);

	if (!mod)
	{
		mod = LoadLibraryA(dll_path);
	}

	auto GetAPI = (pRENDERDOC_GetAPI)GetProcAddress(mod, "RENDERDOC_GetAPI");

	GetAPI(eRENDERDOC_API_Version_1_7_0, (void**)&s_Api);
	
	s_Api->SetLogFilePathTemplate("cache/RHICapture/");
	
	s_Api->SetCaptureOptionU32(eRENDERDOC_Option_RefAllResources, 1);
	
	s_Api->SetCaptureOptionU32(eRENDERDOC_Option_CaptureCallstacks, 1);
	
	s_Api->SetCaptureOptionU32(eRENDERDOC_Option_VerifyBufferAccess, 1);
	
	s_Api->SetCaptureOptionU32(eRENDERDOC_Option_HookIntoChildren, 1);
}

void SetCaptureWindow(void* window)
{
	NEPTUNE_PROFILE_ZONE

	s_Window = (HWND)window;
	
	s_Api->SetActiveWindow(nullptr, s_Window);
}

void BeginEngineScope()
{
	NEPTUNE_PROFILE_ZONE

	s_Api->StartFrameCapture(nullptr, s_Window);
}

void EndEngineScope()
{
	NEPTUNE_PROFILE_ZONE

	s_Api->EndFrameCapture(nullptr, s_Window);
}

void TriggerCapture(uint32_t frames)
{
	NEPTUNE_PROFILE_ZONE

	s_Api->TriggerMultiFrameCapture(frames);
}

#endif