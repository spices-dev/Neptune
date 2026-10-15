/**
* @file RenderTarget.h.
* @brief The RenderTarget Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Resource/Texture.h"
#include "Device/Graphics/Frontend/RHI/Buffer.h"
#include "Device/Graphics/Frontend/RHI/RenderTarget.h"

namespace Neptune::OpenGL {

	/**
	* @brief OpenGL::RenderTarget Class.
	* This class defines the OpenGL::RenderTarget behaves.
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
		* @brief Interface of Copy From Buffer.
		*
		* @param[in] buffer Buffer.
		*
		* @return Returns true if succeeded.
		*/
		bool CopyFromBuffer(const SP<RHI::Buffer>& buffer) override;
		
		/**
		* @brief Interface of SetName.
		*
		* @param[in] name Name.
		*/
		void SetName(const std::string& name) override;
		
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
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Texture::Handle& Handle() const { return m_Texture->Handle(); }
		
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
		
		UP<Resource::Texture> m_Texture;   // @brief Texture.
	};
}

#endif