/**
* @file Converter.cpp.
* @brief The Converter Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Converter.h"

namespace Neptune::FFmpeg {

	AVCodecID ToAVCodecID(VideoOperation op)
	{
		NEPTUNE_PROFILE_ZONE

		switch(op)
		{
			case VideoOperation::DecodeH265: return AV_CODEC_ID_HEVC;
			default:
			{
				NEPTUNE_LOG_CORE(W) << "Unsupported VideoOperation To AVCodecID.";
				return AV_CODEC_ID_H264;
			}
		}
	}
}