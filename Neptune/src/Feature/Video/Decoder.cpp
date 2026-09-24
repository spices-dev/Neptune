/**
* @file Decoder.cpp.
* @brief The Decoder Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Decoder.h"
#include "Device/Graphics/Frontend/RHI/Decoder.h"
#include "Device/Graphics/Frontend/RHI/Capability.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::Video {

	Decoder::Decoder(VideoOperation op)
	{
		NEPTUNE_PROFILE_ZONE

		auto rhiCapability = CreateUP<RHI::Capability>();
		
		if (rhiCapability->IsSupport(Graphic::ECapability::VideoDecode))
		{
			m_Impl = CreateUP<RHI::Decoder>(&op);
		}
		else
		{
			NEPTUNE_LOG_CORE(E) << "RHI Decoder is not supported.";
		}
	}

	Decoder::~Decoder() = default;

	void Decoder::PopPresentPicture() const
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->PopPresentPicture();
	}

	void Decoder::ParserDataChunk(uint8_t* data, uint64_t size) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->ParserDataChunk(data, size);
	}

	uint32_t Decoder::GetPresentPictureCount() const
	{
		NEPTUNE_PROFILE_ZONE

		return m_Impl->GetPresentPictureCount();
	}

	void Decoder::SetDecodeRenderTarget(const SP<RenderTarget>& renderTarget) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetDecodeRenderTarget(renderTarget->GetRHIResource());
	}

	void Decoder::SetReferenceRenderTarget(const SP<RenderTarget>& renderTarget) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetReferenceRenderTarget(renderTarget->GetRHIResource());
	}

	void Decoder::SetFlowVectorRenderTarget(const SP<RenderTarget>& renderTarget) const
	{
		NEPTUNE_PROFILE_ZONE

		m_Impl->SetFlowVectorRenderTarget(renderTarget->GetRHIResource());
	}
}