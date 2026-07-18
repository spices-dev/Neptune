/**
* @file RenderSystem.h.
* @brief The RenderSystem Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "System.h"
#include "Core/Event/EventListener.h"

namespace Neptune {

    class RenderFrontend;
    
    /**
    * @brief RenderSystem Class.
    * This class defines the RenderSystem behaves.
    */
    class RenderSystem : public System, public EventListener
    {
    public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] manager SystemManager.
        */
        explicit RenderSystem(SystemManager* manager);

        /**
        * @brief Destructor Function.
        */
        ~RenderSystem() override;

        /**
        * @brief Interface of system initialize.
        */
        void OnSystemInitialize() override;

        /**
        * @brief Interface of system shutdown.
        */
        void OnSystemShutDown() override;

        /**
        * @brief Interface of system tick run.
        */
        void Tick() override;

        /**
        * @brief Interface of EventListener dispatch event.
        *
        * @param[in] event Event
        */
        void OnEvent(Event& event) override;

        /**
        * @brief Get RenderFrontend.
        *
        * @return Returns RenderFrontend.
        */
        RenderFrontend* GetRenderFrontend() const { return m_RenderFrontend.get(); }

    private:

        /**
        * @brief Engine Event.
        *
        * @param[in] e EngineEvent.
        * 
        * @return Returns true if consumed.
        */
        bool OnEngineEvent(class EngineEvent& e) const;

        /**
        * @brief SlateResizeEvent Event.
        *
        * @param[in] e SlateResizeEvent.
        *
        * @return Returns true if consumed.
        */
        bool OnSlateResizeEvent(class SlateResizeEvent& e) const;

        /**
        * @brief SlateResizeEvent Event.
        *
        * @param[in] e SlateResizeEvent.
        *
        * @return Returns true if consumed.
        */
        bool OnWindowResizeOverEvent(class WindowResizeOverEvent& e) const;

    private:

        UP<RenderFrontend> m_RenderFrontend;    // @brief Render Frontend.
    };
}