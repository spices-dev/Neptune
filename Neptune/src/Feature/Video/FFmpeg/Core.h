/**
* @file Core.h.
* @brief The Core Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavformat/avio.h>
#include <libavcodec/avcodec.h>
#ifndef FF_API_OLD_BSF
#include <libavcodec/bsf.h>
#endif
}

namespace Neptune::FFmpeg {

	constexpr int defaultWidth    = 800;                        // @brief Default Width
	
	constexpr int defaultHeight   = 600;                        // @brief Default Height
	
	constexpr int defaultBitDepth = 8;                          // @brief Default BitDepth
	
	#define FFMPEG_VERSION 7.0                                  // @brief Use FFmpeg 7.0
	
	/**
	* @brief Handle Error Result.
	*
	* @param[in] result FFmpeg Error Code.
	*/
	void HandleResult(int result);

	#define FFMPEG_CHECK(expr)  { auto expr_value = expr; if (expr_value < 0) { HandleResult(expr_value); } }
}