/**
* @file WindowImpl.h.
* @brief The WindowImpl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_WINDOW_EMSCRIPTENGLFW

#include "Core/Core.h"
#include "Window/Window.h"
#include "Core/Event/EventProducer.h"

struct GLFWwindow;

namespace Neptune::EmscriptenGLFW {

    class APIInterface;

    /**
    * @brief WindowImpl Class.
    */
    class WindowImpl : public Window, public EventProducer
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
        *
        * @return Returns Window Extension.
        */
        std::vector<const char*> Extension() const override;

        /**
        * @brief Interface of get native window pointer.
        *
        * @return Returns native window pointer.
        */
        void* NativeWindow() const override;

    private:

        /**
        * @brief Set event/error/input callback.
        */
        void SetInternalCallBack() const;

    private:

        GLFWwindow* m_Windows;             // @brief native window.
        UP<APIInterface> m_APIInterface;   // @brief render backend interface.
    };
}

#endif