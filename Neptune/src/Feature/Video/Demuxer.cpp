/**
* @file Demuxer.cpp.
* @brief The Demuxer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Demuxer.h"

#ifdef NP_PLATFORM_WINDOWS

#include "FFmpeg/Demuxer.h"

#endif

namespace Neptune::Video {

	UP<Demuxer> Demuxer::Create()
	{
		NEPTUNE_PROFILE_ZONE

#ifdef NP_PLATFORM_WINDOWS
		
		return CreateUP<FFmpeg::Demuxer>();
		
#else
		
		return nullptr;
		
#endif
	}

	Demuxer::Demuxer() = default;
	
	Demuxer::~Demuxer() = default;
}