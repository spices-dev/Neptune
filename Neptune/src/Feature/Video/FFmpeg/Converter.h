/**
* @file Converter.h.
* @brief The Converter Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core.h"
#include "Feature/Video/VideoOperation.h"

namespace Neptune::FFmpeg {

	/**
	* @brief Convert VideoOperation to AVCodecID.
	* 
	* @param[in] op VideoOperation.
	* 
	* @return Returns AVCodecID.
	*/
	AVCodecID ToAVCodecID(VideoOperation op);

}

#endif