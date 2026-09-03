/**
* @file WindowImpl.cpp
* @brief The WindowImpl Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_WINDOW_ANDROIDNATIVE

#include "WindowImpl.h"
#include "RenderBackendInterface.h"

#include <android/native_window.h>

namespace Neptune::AndroidNative {

    WindowImpl::WindowImpl(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend, void* payload)
        : Window(implement)
        , m_APIInterface(CreateInterface(backend))
        , m_App()
    {
        if (!payload)
        {
            NEPTUNE_LOG_CORE(C) << "Android Native Window Init Failed.";
            return;
        }
        
       // m_App->onAppCmd = HandleAppCmd;
       // m_App->userData = nullptr;
    }

    WindowImpl::~WindowImpl() = default;
    
    bool WindowImpl::IsWindowActive() const
    {
        NEPTUNE_PROFILE_ZONE

        return false;
        //return !m_App->destroyRequested;
    }

    void WindowImpl::PollEvents() const
    {
        NEPTUNE_PROFILE_ZONE
        
        /*int events;
        android_poll_source* source;
        while (ALooper_pollOnce(m_App->window ? 0 : -1, nullptr, &events, (void**)&source) >= 0)
        {
            if (source) source->process(m_App, source);
            
            //if (m_App->destroyRequested) return;
        }
        
        auto* inputBuffer = android_app_swap_input_buffers(m_App);
        
        if (inputBuffer && inputBuffer->motionEventsCount)
        {
            android_app_clear_motion_events(inputBuffer);
        }*/
    }

    glm::ivec2 WindowImpl::Extent() const
    {
        NEPTUNE_PROFILE_ZONE

        auto* window = static_cast<ANativeWindow*>(NativeWindow());

        return { ANativeWindow_getWidth(window), ANativeWindow_getHeight(window) };
    }

    std::vector<const char*> WindowImpl::Extension() const
    {
        NEPTUNE_PROFILE_ZONE

        return m_APIInterface->Extension();
    }

    void* WindowImpl::NativeWindow() const
    {
        NEPTUNE_PROFILE_ZONE

        return nullptr;
        //return m_App->window;
    }

    void WindowImpl::HandleAppCmd(android_app* app, int32_t cmd)
    {
        /*switch (cmd)
        {
            case APP_CMD_INIT_WINDOW:
                break;
            case APP_CMD_TERM_WINDOW:
                break;
            case APP_CMD_PAUSE:
                break;
            case APP_CMD_RESUME:
                break;
            case APP_CMD_LOST_FOCUS:
                break;
            case APP_CMD_GAINED_FOCUS:
                break;
            default:
                break;
        }*/
    }

}

#endif
