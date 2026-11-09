/**
* @file RenderFrontend.h.
* @brief The RenderFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "RenderDelegate.h"
#include "Core/Event/Event.h"
#include "Core/Event/EventProducer.h"
#include "Device/Graphics/Frontend/RHI/RHI.h"
#include "Enum.h"

#include <vector>
#include <any>
#include <glm/ext/vector_float2.hpp>

namespace Neptune {

    namespace Render {

        class Pass;
    }

    namespace RHI {
        class CmdList;
    }
    
    /**
    * @brief RenderFrontend Class.
    * This class defines the RenderFrontEnd behaves.
    */
    class RenderFrontend : public NonCopyable, public EventProducer, public RHI::RHIDelegate
    {
    public:

        /**
        * @brief Create Render Frontend.
        *
        * @param[in] backend RenderBackendEnum.
        *
        * @return Returns Render Frontend pointer.
        */
        static UP<RenderFrontend> Create(RenderBackendEnum backend);

    public:

        /**
        * @brief Destructor Function.
        */
        ~RenderFrontend() override = default;

        /**
        * @brief Interface of Initialize.
        */
        virtual void OnInitialize();

        /**
        * @brief Interface of ShutDown.
        */
        virtual void OnShutDown();

        /**
        * @brief Interface of Begin a frame.
        * 
        * @param[in] scene Scene.
        */
        virtual void BeginFrame(class Scene* scene) const = 0;

        /**
        * @brief Interface of End a frame.
        * 
        * @param[in] scene Scene.
        */
        virtual void EndFrame(class Scene* scene) const = 0;

        /**
        * @brief Interface of Wait RenderBackend idle.
        */
        virtual void Wait() const = 0;

        /**
        * @brief Interface of Access Infrastructure.
        *
        * @return Returns Infrastructure.
        */
        virtual std::any AccessInfrastructure() const = 0;

        /**
        * @brief Render a frame.
        *
        * @param[in] scene Scene.
        * 
        * @note Order: BeginFrame -> RenderFrame -> EndFrame
        */
        void RenderFrame(class Scene* scene);

        /**
        * @brief Construct Default Passes.
        *
        * @param[in] rtSize Passes RT Size.
        */
        void ConstructDefaultPasses(const glm::vec2& rtSize = { 100.0f, 100.0f });

        /**
        * @brief Construct Slate Pass.
        */
        void ConstructSlatePass();

        /**
        * @brief Get RenderDelegate.
        * 
        * @return Returns RenderDelegate.
        */
        RenderDelegate& GetRenderDelegate() { return m_RenderDelegate; } 
        
    protected:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] backend RenderBackendEnum.
        */
        explicit RenderFrontend(RenderBackendEnum backend) 
            : EventProducer(EventType::WindowResizeOver)
            , m_RenderBackendEnum(backend) 
        {}

        /**
        * @brief Recreate SwapChain.
        */
        virtual void RecreateSwapChain() const;

    private:

        /**
        * @brief Add Pass.
        * 
        * @param[in] pass Pass.
        */
        void AddPass(SP<Render::Pass> pass);

    protected:

        RenderBackendEnum             m_RenderBackendEnum;         // @brief RenderBackendEnum.
        std::vector<SP<Render::Pass>> m_RenderPasses;              // @brief Container of Passes.
        SP<RHI::CmdList>              m_CmdList;                   // @brief CmdList.
        RenderDelegate                m_RenderDelegate;            // @brief RenderDelegate.
        
    };
}