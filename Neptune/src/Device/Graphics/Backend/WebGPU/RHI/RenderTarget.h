/**
* @file RenderTarget.h.
* @brief The RenderTarget Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Resource/Texture.h"
#include "Device/Graphics/Frontend/RHI/RenderTarget.h"

namespace Neptune::WebGPU {

	/**
	* @brief WebGPU::RenderTarget Class.
	* This class defines the WebGPU::RenderTarget behaves.
	*/
	class RenderTarget : public ContextAccessor, public RHI::RHIRenderTarget::Impl
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		RenderTarget(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~RenderTarget() override = default;

	public:

		/**
		* @brief Interface of Create RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateRenderTarget(const RenderTargetCreateInfo& info) override;

		/**
		* @brief Interface of Create BindingID.
		*
		* @return Returns BindingID.
		*/
		void* CreateBindingID() override;

		/**
		* @brief Interface of Copy To RenderTarget.
		*
		* @param[in] target RenderTarget.
		*
		* @return Returns true if succeeded.
		*/
		bool CopyToRenderTarget(const SP<RHI::RenderTarget>& target) override;

		/**
		* @brief Interface of Get Format.
		*
		* @return Returns format.
		*/
		TextureFormat GetFormat() const override;

		/**
		* @brief Interface of Get Width.
		*
		* @return Returns width.
		*/
		uint32_t GetWidth() const override { return m_Texture->Width(); }

		/**
		* @brief Interface of Get Height.
		*
		* @return Returns height.
		*/
		uint32_t GetHeight() const override { return m_Texture->Height(); }

	public:

		/**
		* @brief Set Texture.
		*
		* @return Returns Texture.
		*/
		void SetTexture(const SP<Resource::Texture>& texture) { m_Texture = texture; }

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Texture::Handle& Handle() const { return m_Texture->Handle(); }

		/**
		* @brief Get Unit Handle Interface.
		*
		* @return Returns Unit Handle Interface.
		*/
		SP<Resource::Texture> IHandle() { return m_Texture; }

		/**
		* @brief Get TextureView Unit Handle.
		*
		* @return Returns TextureView Unit Handle.
		*/
		const Unit::TextureView::Handle& GetView() const { return m_Texture->GetView(); }

		/**
		* @brief Get Sampler Unit Handle.
		*
		* @return Returns Sampler Unit Handle.
		*/
		const Unit::Sampler::Handle& GetSampler() const { return m_Texture->GetSampler(); }

		/**
		* @brief Copy to RenderTarget.
		*
		* @param[in] target RenderTarget.
		*/
		bool CopyToRenderTarget(RenderTarget* target) const;

	private:

		/**
		* @brief Create Color RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateColorRenderTarget(const RenderTargetCreateInfo& info);

		/**
		* @brief Create Depth RenderTarget.
		*
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateDepthRenderTarget(const RenderTargetCreateInfo& info);

	private:

		UP<Resource::Texture> m_Texture; // @brief This Texture.
	};
}

#endif