/**
* @file Demuxer.cpp.
* @brief The Demuxer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Demuxer.h"
#include "FFmpeg/Demuxer.h"

namespace Neptune::Video {

	UP<Demuxer> Demuxer::Create()
	{
		NEPTUNE_PROFILE_ZONE

		return CreateUP<FFmpeg::Demuxer>();
	}

	Demuxer::Demuxer() = default;
	
	Demuxer::~Demuxer() = default;
}