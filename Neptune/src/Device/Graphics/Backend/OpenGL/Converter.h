/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core.h"
#include "Asset/SOP/Enum.h"
#include "Resource/Texture/Texture.h"

namespace Neptune::OpenGL {

	/**
	* @brief Convert ECullMode to GLenum.
	* 
	* @param[in] c ECullMode.
	* 
	* @return Returns GLenum.
	*/
	GLenum ToGLCullMode(ECullMode c);
	
	/**
	* @brief Convert ETopology to GLenum.
	* 
	* @param[in] t ETopology.
	* 
	* @return Returns GLenum.
	*/
	GLenum ToGLTopology(ETopology t);
	
	/**
	* @brief Convert TextureFormat to GLenum.
	* 
	* @param[in] f TextureFormat.
	* 
	* @return Returns GLenum.
	*/
	GLenum ToGLInternalFormat(TextureFormat f);

}

#endif