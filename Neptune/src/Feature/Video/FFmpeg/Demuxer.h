/**
* @file Demuxer.h.
* @brief The Demuxer Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_PLATFORM_WINDOWS

#include "Core/Core.h"
#include "Core.h"
#include "Feature/Video/Demuxer.h"

namespace Neptune::FFmpeg {

	/**
	* @brief FFmpeg Video Demuxer Class.
	*/
	class Demuxer : public Video::Demuxer
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		Demuxer() = default;
		
		/**
		* @brief Destructor Function.
		*/
		~Demuxer() override = default;

		 /**
		 * @brief Initialize Demuxer.
		 * 
		 * @param[in] path Video File Path.
		 * @param[in] op VideoOperation.
		 */
		 void Initialize(const std::filesystem::path& path, VideoOperation op) override;

		/**
		 * @brief Demux Frame.
		 * 
		 * @return Returns Data Packet.
		 */
         Video::Packet DemuxFrame() override;

	private:

		AVFormatContext*              m_Fmtc        = nullptr;
        AVIOContext*                  m_Avioc       = nullptr;
        AVPacket*                     m_Pkt         = nullptr;
        AVPacket*                     m_PktFiltered = nullptr;
        AVBSFContext*                 m_Bsfc        = nullptr;
        AVCodecParameters             m_Params;

        int                           m_VideoStream;
        int                           m_CodedLumaBitDepth;
        int                           m_CodedChromaBitDepth;
        int                           m_Profile;
        bool                          m_IsStreamDemuxer;
	};
}

#endif