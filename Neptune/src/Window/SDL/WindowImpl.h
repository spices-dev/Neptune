/**
* @file WindowImpl.h.
* @brief The WindowImpl Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_WINDOW_SDL

#include "Core/Core.h"
#include "Window/Window.h"
#include "Core/Event/EventProducer.h"

struct SDL_Window;
union  SDL_Event;

namespace Neptune::SDL {

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
        * @brief Interface of window poll events.
        * 
        * @return Returns true if window is active.
        */
        bool PollEvents() const override;

        /**
        * @brief Interface of window get extent.
        */
        glm::uvec2 Extent() const override;

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
        * @brief Process Event.
        * 
        * @param[in] e SDL_Event.
        */
        void ProcessEvent(const SDL_Event& e) const;

    private:
        
        SDL_Window*      m_Windows;           // @brief native window.
        UP<APIInterface> m_APIInterface;      // @brief render backend interface.
    };
}

#endif