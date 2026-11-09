/**
* @file GraphicsBackend.h.
* @brief The GraphicsBackend Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Frontend/GraphicsFrontend.h"
#include "Infrastructure/Enum.h"
#include "Device/Graphics/Backend/Common/Infrastructure/Context.h"

namespace Neptune::OpenGL {

    /**
    * @brief GraphicsBackend Class.
    * This class defines the GraphicsBackend behaves.
    */
    class GraphicsBackend : public GraphicsFrontend
    {
    public:

        using Context = Graphic::Common::IContext<EInfrastructure>;

    public:

        /**
        * @brief Constructor Function.
        */
        GraphicsBackend();

        /**
        * @brief Destructor Function.
        */
        ~GraphicsBackend() override;

        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] window Window.
        */
        void OnInitialize(const Window* window = nullptr) override;

        /**
        * @brief Interface of ShutDown.
        */
        void OnShutDown() override;

        /**
        * @brief Interface of Wait RenderBackend idle.
        */
        void Wait() const override;

        /**
        * @brief Interface of CreateRHI.
        *
        * @param[in] e ERHI.
        * @param[in] payload RHI Payload.
        *
        * @return Returns RHI::Impl
        */
        UP<RHI::RHIImplEmpty> CreateRHI(RHI::ERHI e, void* payload) const override;

        /**
        * @brief Interface of Access Infrastructure.
        *
        * @return Returns Infrastructure.
        */
        Graphic::AInfrastructures AccessInfrastructure() const override;

        /**
        * @brief Get Context.
        *
        * @return Returns Context.
        */
        Context& GetContext() const;

    private:

        UP<Context> m_Context; // @brief This Context.
    };
}

#endif