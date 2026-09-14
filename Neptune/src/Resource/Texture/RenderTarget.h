#pragma once
#include "Core/Core.h"
#include "Texture.h"
#include "Core/Memory/Enum.h"

namespace Neptune {

	namespace RHI {
	
		class RenderTarget;
	}

	struct RenderTargetCreateInfo
	{
		uint32_t          width        = 100;
		uint32_t          height       = 100;
		TextureDomain     domain       = TextureDomain::Texture2D;
		TextureFormat     format       = TextureFormat::RGBA8_UNORM;
		EMemory           memoryUsage  = EMemory::Device;
	};

	enum class AttachmentOP : uint8_t
	{
		Clear = 0,
		Load,

		Count
	};

	enum class AttachmentLayout : uint8_t
	{
		Undefined = 0,
		General,
		Attachment,
		ShaderRead,

		Count
	};

	struct RenderTargetAttachmentInfo
	{
		bool               enableBlend = false;
		AttachmentOP       loadOp = AttachmentOP::Clear;
		AttachmentLayout   inLayout = AttachmentLayout::Undefined;
		AttachmentLayout   outLayout = AttachmentLayout::Attachment;
	};

	class RenderTarget
	{
	public:

		RenderTarget();

		RenderTarget(const RenderTargetCreateInfo& info);

		virtual ~RenderTarget() = default;

		SP<RHI::RenderTarget> GetRHIResource() { return m_RHIResource; }

		void SetName(const std::string& name) { m_Name = name; }

		bool CopyToRenderTarget(const SP<RenderTarget>& target) const;

	private:

		std::string           m_Name;
		SP<RHI::RenderTarget> m_RHIResource;
	};
}
