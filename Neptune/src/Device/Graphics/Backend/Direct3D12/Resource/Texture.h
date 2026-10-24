/**
* @file Texture.h.
* @brief The Texture Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

#include "Core/Core.h"
#include "Device/Graphics/Backend/Direct3D12/Infrastructure/Infrastructure.h"
#include "Device/Graphics/Backend/Direct3D12/Unit/Resource.h"

namespace Neptune::Direct3D12::Resource {

	/**
	* @brief Direct3D12::Texture Class.
	* This class defines the Direct3D12::Texture behaves.
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
		void SetTexture(Unit::Resource::Handle texture);
		
		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Resource::Handle& Handle() const { return m_Texture.GetHandle(); }

		/**
		* @brief Get Unit Handle Interface.
		* 
		* @return Returns Unit Handle Interface.
		*/
		const Unit::Resource& IHandle() const { return m_Texture; }
		
		/**
		* @brief Create Texture.
		*
		* @param[in] desc D3D12_RESOURCE_DESC.
		*/
		void CreateTexture(const D3D12_RESOURCE_DESC& desc);
		
		/**
		* @brief Set Image name.
		*
		* @param[in] name Image name.
		*/
		void SetName(const std::string& name) const;
		
		/**
		* @brief Get Texture Format.
		*
		* @return Returns Texture Format.
		*/
		const DXGI_FORMAT& GetFormat() const { return m_Format; }

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

		Unit::Resource m_Texture;                              // @brief This Texture.
		
		DXGI_FORMAT                  m_Format{};               // @brief VkFormat.
		uint32_t                     m_LayerCount = 1;         // @brief Layer Count.

		uint32_t                     m_Width{};                // @brief Width.
		uint32_t                     m_Height{};               // @brief Height.
	};
}

#endif