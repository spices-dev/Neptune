/**
* @file WindowImpl.h
* @brief The WindowImpl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_WINDOW_ANDROIDNATIVE

#include "Core/Core.h"
#include "Window/Window.h"

struct android_app;

namespace Neptune::AndroidNative {

    class APIInterface;
    
    /**
    * @brief WindowImpl Class.
    */
    class WindowImpl : public Window
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] initInfo WindowInfo.
        * @param[in] implement WindowImplement.
        * @param[in] backend RenderBackendEnum.
        * @param[in] payload PayLoad.
        */
        WindowImpl(const WindowInfo& initInfo, WindowImplement implement, RenderBackendEnum backend, void* payload = nullptr);

        /**
        * @brief Destructor Function.
        */
        ~WindowImpl() override;

        /**
        * @brief Interface of determine if window is still active.
        * 
        * @return Returns true if window is active.
        */
        bool IsWindowActive() const override;

        /**
        * @brief Interface of window poll events.
        */
        void PollEvents() const override;

        /**
        * @brief Interface of window get extent.
        */
        glm::ivec2 Extent() const override;

        /**
        * @brief Get Window Extension.
        */
        std::vector<const char*> Extension() const override;

        /**
        * @brief Interface of get native window pointer.
        */
        void* NativeWindow() const override;

    private:

        /**
        * @brief game-activity lifecycle command callback.
        * @param[in] app android_app handle.
        * @param[in] cmd Lifecycle command.
        */
        static void HandleAppCmd(android_app* app, int32_t cmd);
        
    private:
        
        android_app* m_App;                // @brief game-activity App.
        UP<APIInterface> m_APIInterface;   // @brief render backend interface.
    };

}

#endif
