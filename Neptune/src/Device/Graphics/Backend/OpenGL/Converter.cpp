/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_OPENGL

#include "Converter.h"

namespace Neptune::OpenGL {

	GLenum ToGLCullMode(ECullMode c)
	{
		NEPTUNE_PROFILE_ZONE

		using enum ECullMode;
		
		switch (c)
		{
			case None:              return GL_NONE;
			case Front:             return GL_FRONT;
			case Back:              return GL_BACK;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported ECullMode To GLenum.";
				return GL_NONE;
			}
		}
	}
	
	GLenum ToGLTopology(ETopology t)
	{
		NEPTUNE_PROFILE_ZONE

		using enum ETopology;
		
		switch (t)
		{
			case TriangleList:              return GL_TRIANGLES;
			case TriangleStrip:             return GL_TRIANGLE_STRIP;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported ECullMode To GLenum.";
				return GL_NONE;
			}
		}
	}
	
	GLenum ToGLInternalFormat(TextureFormat f)
	{
		NEPTUNE_PROFILE_ZONE

		using enum TextureFormat;
		
		switch (f)
		{
			case RGBA8_UNORM:                    return GL_RGBA8;
			case RGBA16_SFLOAT:                  return GL_RGBA16F;
			default:
			{
				NEPTUNE_LOG_CORE(E) << "Unsupported TextureFormat To GLenum.";
				return GL_NONE;
			}
		}
	}
}

#endif