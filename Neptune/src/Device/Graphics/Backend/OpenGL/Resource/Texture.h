/**
* @file Texture.h.
* @brief The Texture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_OPENGL

#include "Core/Core.h"
#include "Device/Graphics/Backend/OpenGL/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/OpenGL/Unit/Texture.h"
#include "Device/Graphics/Backend/OpenGL/Unit/Sampler.h"
#include "Resource/Texture/RenderTarget.h"

namespace Neptune::OpenGL::Resource {

	/**
	* @brief OpenGL::Texture Class.
	* This class defines the OpenGL::Texture behaves.
	*/
	class Texture : public ContextAccessor
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		*/
		explicit Texture(Context& context) : ContextAccessor(context) {}

		/**
		* @brief Destructor Function.
		*/
		~Texture() override = default;

		/**
		* @brief Set Unit Handle.
		* 
		* @param[in] texture Unit Handle.
		*/
		void SetTexture(Unit::Texture::Handle texture);

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Texture::Handle& Handle() const { return m_Texture.GetHandle(); }

		/**
		* @brief Create Texture.
		* 
		* @param[in] info RenderTargetCreateInfo.
		*/
		void CreateTexture(const RenderTargetCreateInfo& info);
		
		/**
		* @brief Create View.
		*/
		void CreateSampler();
		
		/**
		* @brief Set Image name.
		*
		* @param[in] name Image name.
		*/
		void SetName(const std::string& name) const;

		/**
		* @brief Get Sampler Unit Handle.
		*
		* @return Returns Sampler Unit Handle.
		*/
		const Unit::Sampler::Handle& GetSampler() const { return m_TextureSampler.GetHandle(); }

		/**
		* @brief Get Texture Format.
		*
		* @return Returns Texture Format.
		*/
		int GetFormat() const { return m_Format; }

		/**
		* @brief Get Texture Layer Count.
		*
		* @return Returns Texture Layer Count.
		*/
		uint32_t GetLayerCount() const { return m_LayerCount; }

		/**
		* @brief Get Texture Width.
		*
		* @return Returns Texture Width.
		*/
		uint32_t Width() const { return m_Width; }

		/**
		* @brief Get Texture Height.
		*
		* @return Returns Texture Height.
		*/
		uint32_t Height() const { return m_Height; }
		
	private:

		Unit::Texture                m_Texture;                // @brief This Texture.
		Unit::Sampler                m_TextureSampler;         // @brief This Sampler.
		int                          m_Format;                 // @brief WGPUTextureFormat.
		int                          m_LayerCount;             // @brief LayerCount.
		int                          m_Width;                  // @brief Width.
		int                          m_Height;                 // @brief Height.

	};
}

#endif