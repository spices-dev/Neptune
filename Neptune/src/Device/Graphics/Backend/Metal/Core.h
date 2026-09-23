/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_METAL

#define NP_GRAPHICS_METAL_CORE

#include "Core/Core.h"
#include "Version.h"
#include "Render/Frontend/Core.h"

#include <functional>

namespace Neptune::Metal {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	#define METAL_DEV_VERSION                                              // @brief Use Metal.

	/**
	* @brief Result Delegate Class.
	*/
    struct HandleResultDelegate
    {
        using Handler = std::function<void(NS::Error* result)>;

		/**
		* @brief Set Handler.
		* 
		* @param[in] fn Handler.
		*/
        static void SetHandler(const Handler& fn);

		/**
		* @brief Get Handler.
		*
		* @return Returns Handler.
		*/
        static const Handler& GetHandler();
    };
	
	/**
	* @brief Handle Error Result.
	* 
	* @param[in] result NS::Error*
	*/
	void HandleResult(const NS::Error* result);

	#define METAL_CHECK(expr)  { NS::Error* result = nullptr; expr; if(result){ std::invoke(HandleResultDelegate::GetHandler(), result); NEPTUNE_BREAK } }
}

#endif