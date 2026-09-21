/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGLES

#include "Core.h"

namespace Neptune::OpenGLES {

	namespace {
	
		HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void GL_APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam
	) {
		NEPTUNE_PROFILE_ZONE

		std::stringstream ss;

		ss <<
		"OpenGLES Validation:\n			" <<
		"MessageIdNumber: " << id <<
		"\n			MessageIdName: " << source;
		ss << "\n			Message: " << message;

		switch (type)
		{
			case GL_DEBUG_SEVERITY_NOTIFICATION:
			{
				NEPTUNE_LOG_CORE(T) << ss.str();
				break;
			}
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			case GL_DEBUG_TYPE_PORTABILITY:
			case GL_DEBUG_TYPE_PERFORMANCE:
			{
				NEPTUNE_LOG_CORE(W) << ss.str();
				break;
			}
			case GL_DEBUG_TYPE_ERROR:
			{
				NEPTUNE_LOG_CORE(E) << ss.str();
				break;
			}
			case GL_DEBUG_TYPE_PUSH_GROUP: break;
			case GL_DEBUG_TYPE_POP_GROUP: break;
			default:
			{
				NEPTUNE_LOG_CORE(T) << ss.str();
				break;
			}
		}
	}
	
	void HandleResult(GLenum result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result == GL_NO_ERROR) return;

		const char* label = "";
		switch (result)
		{
			case GL_INVALID_ENUM:                                        label = "Invalid Enum";                        break;
			case GL_INVALID_VALUE:                                       label = "Invalid Value";                       break;
			case GL_INVALID_OPERATION:                                   label = "Invalid Operation";                   break;
			case GL_STACK_OVERFLOW:                                      label = "Stack OverFlow";                      break;
			case GL_STACK_UNDERFLOW:                                     label = "Stack UnderFlow";                     break;
			case GL_OUT_OF_MEMORY:                                       label = "Out of Memory";                       break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:                       label = "Invalid Framebuffer Operation";       break;
			case GL_CONTEXT_LOST:                                        label = "Context Lost";                        break;
			default:                                                     label = "Unknown Error";                       break;
		}

        NEPTUNE_LOG_CORE(E) << "OpenGLES Error: [ " << label << " ]";
	}
}

#endif