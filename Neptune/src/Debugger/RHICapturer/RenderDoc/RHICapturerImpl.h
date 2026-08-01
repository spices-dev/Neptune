/**
* @file RHICapturerImpl.h file.
* @brief The RHICapturerImpl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_RHICAPTURER_RENDERDOC

#include "Core/Core.h"

namespace Neptune::RenderDoc {
    
    /**
    * @brief Initialize RenderDoc evvironment.
    * 
    */
    void Initialize();

    /**
    * @brief Set Captured WindowContext.
    * 
    * @param[in] Native Window.
    */
    void SetCaptureWindow(void* window);

    /**
    * @brief Begin Engine Main Scope.
    */
    void BeginEngineScope();

    /**
    * @brief End Engine Main Scope.
    */
    void EndEngineScope();

    /**
    * @brief Trigger Capture Next Frames.
    * 
    * @param[in] frames Frame Count.
    */
    void TriggerCapture(uint32_t frames = 1);

}

#endif