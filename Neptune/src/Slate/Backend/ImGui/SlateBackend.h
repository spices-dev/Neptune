/**
* @file SlateBackend.h.
* @brief The SlateBackend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Slate/Frontend/SlateFrontend.h"

namespace Neptune::imgui {

    class RenderInterface;
    class WindowInterface;

    /**
    * @brief imgui::SlateBackend Class.
    * This class defines the imgui::SlateBackend behaves.
    */
	class SlateBackend : public SlateFrontend
	{
	public:

        /**
        * @brief Constructor Function.
        * 
        * @param[in] renderBackend RenderBackendEnum.
        * @param[in] windowImpl WindowImplement.
        */
        SlateBackend(RenderBackendEnum renderBackend, WindowImplement windowImpl);

        /**
        * @brief Destructor Function.
        */
		~SlateBackend() override = default;

        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] infrastructure RenderFrontend Infrastructure.
        */
		void OnInitialize(const AInfrastructures& infrastructure) const override;

        /**
        * @brief Interface of ShutDown.
        */
		void OnShutDown() const override;

        /**
        * @brief Interface of Begin a frame.
        */
        void BeginFrame() const override;
		
        /**
        * @brief Interface of End a frame.
        */
        void EndFrame() const override;

		/**
		* @brief Interface of Submit Frame RHI.
		* 
		* @param[in] payload RenderFrontend Payload.
		*/
		void SubmitFrameRHI(void* payload = nullptr) const override;

	private:

        UP<RenderInterface> m_RenderInterface;         // @brief render backend interface.
        UP<WindowInterface> m_WindowInterface;         // @brief window backend interface.

        RenderBackendEnum m_RenderBackendEnum;         // @brief RenderBackendEnum.
        WindowImplement   m_WindowImplement;           // @brief WindowImplement.
	};

}