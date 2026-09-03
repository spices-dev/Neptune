/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Core.h"
#include "Converter.h"

namespace Neptune::FFmpeg {
	
	void HandleResult(int result)
	{
        NEPTUNE_PROFILE_ZONE

		if (result >= 0) return;

		char err_buf[AV_ERROR_MAX_STRING_SIZE];
		av_strerror(result, err_buf, sizeof(err_buf));

		NEPTUNE_LOG_CORE(E) << "FFmpeg Error Code: " << result << ", desc: "<< err_buf;
	}
}

#endif