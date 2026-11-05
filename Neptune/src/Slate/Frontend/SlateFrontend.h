/**
* @file SlateFrontend.h.
* @brief The SlateFrontend Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Core/NonCopyable.h"
#include "Enum.h"
#include "Render/Frontend/Enum.h"
#include "Window/Enum.h"

#include <unordered_map>
#include <any>

namespace Neptune {

    /**
    * @brief SlateFrontend Class.
    * This class defines the SlateFrontend behaves.
    */
	class SlateFrontend : public NonCopyable
	{
    public:

        /**
        * @brief Create Slate Frontend.
        *
        * @param[in] slateBackend SlateBackendEnum.
        * @param[in] renderBackend RenderBackendEnum.
        * @param[in] windowImpl WindowImplement.
        * 
        * @return Returns Slate Frontend pointer.
        */
        static UP<SlateFrontend> Create(SlateBackendEnum slateBackend, RenderBackendEnum renderBackend, WindowImplement windowImpl);

	public:

        /**
        * @brief Destructor Function.
        */
        virtual ~SlateFrontend();

        /**
        * @brief Interface of Initialize.
        * 
        * @param[in] infrastructure RenderFrontend Infrastructure.
        */
		virtual void OnInitialize(const std::any& infrastructure) const = 0;

        /**
        * @brief Interface of ShutDown.
        */
		virtual void OnShutDown() const = 0;

        /**
        * @brief Interface of Begin a frame.
        */
        virtual void BeginFrame() const = 0;

        /**
        * @brief Interface of End a frame.
        */
        virtual void EndFrame() const = 0;

		/**
		* @brief Interface of Submit Frame RHI.
		* 
		* @param[in] payload RenderFrontend Payload.
		* 
		* @note Order: BeginFrame -> EndFrame -> SubmitFrameRHI
		*/
		virtual void SubmitFrameRHI(void* payload = nullptr) const = 0;
		
    protected:

        /**
        * @brief Constructor Function.
        *
        * @param[in] backend RenderBackendEnum.
        */
        SlateFrontend(SlateBackendEnum backend);

	private:

        SlateBackendEnum  m_SlateBackendEnum;         // @brief SlateBackendEnum.
	};

}