/**
* @file Texture.h.
* @brief The Texture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

#include "Core/Core.h"
#include "Device/Graphics/Backend/WebGPU/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Texture.h"
#include "Device/Graphics/Backend/WebGPU/Unit/TextureView.h"
#include "Device/Graphics/Backend/WebGPU/Unit/Sampler.h"

namespace Neptune::WebGPU::Resource {

	/**
	* @brief WebGPU::Texture Class.
	* This class defines the WebGPU::Texture behaves.
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
		* @param[in] desc WGPUTextureDescriptor.
		*/
		void CreateTexture(const WGPUTextureDescriptor& desc);
		
		/**
		* @brief Create Texture View.
		*
		* @param[in] desc WGPUTextureViewDescriptor.
		*/
		void CreateTextureView(const WGPUTextureViewDescriptor& desc);
		
		/**
		* @brief Create View.
		*
		* @param[in] desc WGPUSamplerDescriptor.
		*/
		void CreateSampler(const WGPUSamplerDescriptor& desc);
		
		/**
		* @brief Set Image name.
		*
		* @param[in] name Image name.
		*/
		void SetName(const std::string& name) const;

		/**
		* @brief Get TextureView Unit Handle.
		*
		* @return Returns TextureView Unit Handle.
		*/
		const Unit::TextureView::Handle& GetView() const { return m_TextureView.GetHandle(); }

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
		const WGPUTextureFormat& GetFormat() const { return m_Format; }

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
		Unit::TextureView            m_TextureView;            // @brief This TextureView.
		Unit::Sampler                m_TextureSampler;         // @brief This Sampler.
		WGPUTextureFormat            m_Format;                 // @brief WGPUTextureFormat.
		uint32_t                     m_LayerCount;             // @brief LayerCount.
		uint32_t                     m_Width;                  // @brief Width.
		uint32_t                     m_Height;                 // @brief Height.

	};
}

#endif