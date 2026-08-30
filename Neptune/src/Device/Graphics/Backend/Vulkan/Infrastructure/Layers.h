/**
* @file Layers.h.
* @brief The Layers Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Layer/Context.h"

namespace Neptune::Vulkan {

	using ILayers = IInfrastructure<class Layers, EInfrastructure::Layers>;

	/**
	* @brief Vulkan::Layers Class.
	* This class defines the Vulkan::Layers behaves.
	*/
	class Layers : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Layers(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Layers() override = default;
		
		/**
		* @brief Get Layer::LContext.
		*
		* @return Returns Layer::LContext.
		*/
		Layer::LContext<ELayer>& GetContext() { return m_Context; }

		/**
		* @brief Get Layer::LContext.
		* 
		* @return Returns Layer::LContext.
		*/
		const Layer::LContext<ELayer>& GetContext() const { return m_Context; }
		
		/**
		* @brief Build Layer Setting Chain.
		*
		* @param[in,out] settings VkLayerSettingEXT.
		*/
		void BuildLayerSettingChain(std::vector<VkLayerSettingEXT>& settings);

    private:
        
        /**
        * @brief Create Extension.
        */
        void Create();
		
    private:
    
        Layer::LContext<ELayer> m_Context; // @brief This EContext.
		
	};
	
}

#endif