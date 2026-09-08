/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGLES

#define NP_GRAPHICS_OPENGLES_CORE

#include "Core/Core.h"
#include "Render/Frontend/Core.h"

#include <functional>
#include <GLES3/gl32.h>

namespace Neptune::OpenGLES {

	constexpr uint32_t MaxFrameInFlight = Neptune::MaxFrameInFlight;       // @brief Frames In Flight.

	#define OPENGLES_VERSION  "es3.2"                                      // @brief Use OpenGLES 3.2.

	/**
	* @brief Result Delegate Class.
	*/
    struct HandleResultDelegate
    {
        using Handler = std::function<void(GLenum)>;

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
	* @brief Debug Callback Functor.
	*
	* @param[in] source Message Source.
	* @param[in] type Message Type.
	* @param[in] id Message unique id.
	* @param[in] severity Message Level.
	* @param[in] length Message bytes.
	* @param[in] message Message data.
	* @param[im] userParam Callback.
	*/
	void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam
	);
	
	/**
	* @brief Handle Error Result.
	*
	* @param[in] result GLenum.
	*/
	void HandleResult(GLenum result);

	#define OPENGLES_CHECK  { auto expr_value = glGetError(); if (expr_value != GL_NO_ERROR) { std::invoke(HandleResultDelegate::GetHandler(), expr_value); } }
}

#endif