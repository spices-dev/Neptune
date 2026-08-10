/**
* @file Demuxer.cpp.
* @brief The Demuxer Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Demuxer.h"
#include "Converter.h"

namespace Neptune::FFmpeg {

    namespace {

        /**
        * @brief CreateFormat Context.
        *
        * @param[in] pFilePath FilePath.
        * @param[in] videoCodecId AVCodecID.
        * 
        * @return Returns AVFormatContext*.
        */
        AVFormatContext* CreateFormatContext(const char* pFilePath, AVCodecID videoCodecId) 
        {
            NEPTUNE_PROFILE_ZONE

            FFMPEG_CHECK(avformat_network_init())

            auto ctx = avformat_alloc_context();

            ctx->video_codec_id = videoCodecId;
            
            if (videoCodecId != AV_CODEC_ID_NONE) 
            {
                ctx->video_codec = avcodec_find_decoder(videoCodecId);
            }
            
            FFMPEG_CHECK(avformat_open_input(&ctx, pFilePath, nullptr, nullptr))
            
            return ctx;
        }
    }

	void Demuxer::Initialize(const std::filesystem::path& path, VideoOperation op)
	{
        NEPTUNE_PROFILE_ZONE

        m_Fmtc = CreateFormatContext(path.generic_string().c_str(), ToAVCodecID(op));

		if (!m_Fmtc) 
        {
            NEPTUNE_LOG_CORE(E) << "No AVFormatContext provided.";
            return;
        }

        NEPTUNE_LOG_CORE(I) << "Media format: " << m_Fmtc->iformat->long_name << " (" << m_Fmtc->iformat->name << ")";

        FFMPEG_CHECK(avformat_find_stream_info(m_Fmtc, nullptr))
        
        m_VideoStream = av_find_best_stream(m_Fmtc, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
        
        if (m_VideoStream < 0) 
        {
            NEPTUNE_LOG_CORE(E) << "FFmpeg error: Could not find stream in input file.";
            return;
        }

        m_Params = *m_Fmtc->streams[m_VideoStream]->codecpar;

        m_CodedLumaBitDepth   = 8;
        m_CodedChromaBitDepth = 8;
        switch (m_Params.format) {
            case AV_PIX_FMT_YUV420P10LE:
            case AV_PIX_FMT_YUV422P10LE:
            case AV_PIX_FMT_YUV444P10LE:
            {
                m_CodedLumaBitDepth   = 10;
                m_CodedChromaBitDepth = 10;
                break;
            }
            case AV_PIX_FMT_YUV420P12LE:
            case AV_PIX_FMT_YUV444P12LE:
            {
                m_CodedLumaBitDepth   = 12;
                m_CodedChromaBitDepth = 12;
                break;
            }
            default:
                break;
        }
        m_IsStreamDemuxer = (!strcmp(m_Fmtc->iformat->long_name, "QuickTime / MOV") ||
                             !strcmp(m_Fmtc->iformat->long_name, "FLV (Flash Video)") ||
                             !strcmp(m_Fmtc->iformat->long_name, "Matroska / WebM"));

        m_Profile = m_Params.profile & 0xFF;

        m_Pkt       = av_packet_alloc();
        m_Pkt->data = nullptr;
        m_Pkt->size = 0;
        m_PktFiltered       = av_packet_alloc();
        m_PktFiltered->data = nullptr;
        m_PktFiltered->size = 0;

        if (m_IsStreamDemuxer) 
        {
            const AVBitStreamFilter* bsf = nullptr;

            if (m_Params.codec_id == AV_CODEC_ID_H264) 
            {
                bsf = av_bsf_get_by_name("h264_mp4toannexb");
            } 
            else if (m_Params.codec_id == AV_CODEC_ID_HEVC) 
            {
                bsf = av_bsf_get_by_name("hevc_mp4toannexb");
            } 
            else if (m_Params.codec_id == AV_CODEC_ID_AV1) 
            {
                bsf = av_bsf_get_by_name("av1_metadata");
            } 
            else if (m_Params.codec_id == AV_CODEC_ID_VP9) 
            {
                bsf = av_bsf_get_by_name("vp9_metadata");
            }

            if (!bsf) {
                NEPTUNE_LOG_CORE(E) << "FFmpeg error: av_bsf_get_by_name(): failed";
                return;
            }
            
            FFMPEG_CHECK(av_bsf_alloc(bsf, &m_Bsfc))
            m_Bsfc->par_in = m_Fmtc->streams[m_VideoStream]->codecpar;
            FFMPEG_CHECK(av_bsf_init(m_Bsfc))
        }

        if (m_Params.width == 0) 
        {
            m_Params.width = defaultWidth;
        }

        if (m_Params.width == 0) 
        {
            m_Params.width = defaultHeight;
        }

        if (m_Params.format == -1) 
        {
            m_CodedLumaBitDepth = defaultBitDepth;
        }
	}

    Video::Packet Demuxer::DemuxFrame()
    {
        NEPTUNE_PROFILE_ZONE

        Video::Packet packet{};

        if (!m_Fmtc)
        {
            return packet;
        }

        if (m_Pkt->data) 
        {
            av_packet_unref(m_Pkt);
        }

        int e = 0;
        while ((e = av_read_frame(m_Fmtc, m_Pkt)) >= 0 && m_Pkt->stream_index != m_VideoStream) 
        {
            av_packet_unref(m_Pkt);
        }

        FFMPEG_CHECK(e)

        if (m_IsStreamDemuxer) 
        {
            if (m_PktFiltered->data) 
            {
                av_packet_unref(m_PktFiltered);
            }
            FFMPEG_CHECK(av_bsf_send_packet(m_Bsfc, m_Pkt))
            FFMPEG_CHECK(av_bsf_receive_packet(m_Bsfc, m_PktFiltered))
            packet.data = m_PktFiltered->data;
            packet.size = m_PktFiltered->size;
            return packet;
        } 

        packet.data = m_Pkt->data;
        packet.size = m_Pkt->size;
        return packet;
    }
}