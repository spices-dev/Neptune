/**
* @file RHICapturerImpl.cpp.
* @brief The RHICapturerImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_RHICAPTURER_RENDERDOC

#include "RHICapturerImpl.h"

#include <Windows.h>
#include <renderdoc_app.h>

namespace {

	constexpr char dll_path[] = "renderdoc.dll";    // @brief RenderDoc DLL Path
	
	RENDERDOC_API_1_7_0* s_Api = nullptr;
	HWND s_hwnd = NULL;
	
}

void InitRenderDoc()
{
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

void SetActiveWindow(void* hwnd)
{
	s_hwnd = (HWND)hwnd;
	
	s_Api->SetActiveWindow(nullptr, s_hwnd);
}

void BeginCapture()
{
	s_Api->StartFrameCapture(nullptr, s_hwnd);
}

void EndCapture()
{
	s_Api->EndFrameCapture(nullptr, s_hwnd);
}

void TriggerCapture()
{
	s_Api->TriggerMultiFrameCapture(1);
}

#endif