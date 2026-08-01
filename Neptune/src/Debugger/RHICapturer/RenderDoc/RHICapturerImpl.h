/**
* @file RHICapturerImpl.h file.
* @brief The RHICapturerImpl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_RHICAPTURER_RENDERDOC

#include "Core/Core.h"

void InitRenderDoc();
void SetActiveWindow(void* hwnd);
void BeginCapture();
void EndCapture();
void TriggerCapture();

#endif