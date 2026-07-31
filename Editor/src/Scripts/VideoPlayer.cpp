/**
* @file VideoPlayer.cpp.
* @brief The VideoPlayer Class Implementation.
* @author Spices.
*/

#include "VideoPlayer.h"
#include <Feature/Video/Demuxer.h>
#include <Feature/Video/Decoder.h>
#include <Resource/ResourcePool.h>
#include <Resource/Texture/RenderTarget.h>
#include <Device/Graphics/Frontend/RHI/RenderTarget.h>

namespace Neptune::Editor {

	VideoPlayer::VideoPlayer(const std::filesystem::path& path) : m_InFile{ path } {}

	VideoPlayer::~VideoPlayer() = default;

	void VideoPlayer::OnAttached()
	{
		NEPTUNE_PROFILE_ZONE
		
        m_Demuxer = Video::Demuxer::Create();
		
		m_Demuxer->Initialize(m_InFile, VideoOperation::DecodeH265);

		m_Decoder = CreateUP<Video::Decoder>(VideoOperation::DecodeH265);
		
		m_Decoder->SetDecodeRenderTarget(ResourcePool<RenderTarget>::Instance().GetResource("CurrDecodeRT"));
	}
	
	void VideoPlayer::OnTick()
	{
		NEPTUNE_PROFILE_ZONE
		
		while(!m_Decoder->GetPresentPictureCount())
		{
			auto packet = m_Demuxer->DemuxFrame();

			if (!packet.size) return;

			m_Decoder->ParserDataChunk(packet.data, packet.size);
		}

		m_Decoder->PopPresentPicture();
	}

}