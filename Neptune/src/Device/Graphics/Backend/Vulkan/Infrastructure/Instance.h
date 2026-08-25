/**
* @file Instance.h.
* @brief The Instance Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Unit/Instance.h"
#include "Device/Graphics/Backend/Vulkan/Unit/DebugUtilsMessenger.h"

#include <vector>

namespace Neptune::Vulkan {

	using IInstance = IInfrastructure<class Instance, EInfrastructure::Instance>;

	/**
	* @brief Vulkan::Instance Class.
	* This class defines the Vulkan::Instance behaves.
	*/
	class Instance : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		*/
		Instance(Context& context, EInfrastructure e);

		/**
		* @brief Destructor Function.
		*/
		~Instance() override = default;

		/**
		* @brief Get Unit Handle.
		*
		* @return Returns Unit Handle.
		*/
		const Unit::Instance::Handle& Handle() const { return m_Instance.GetHandle(); }

	private:

		/**
		* @brief Create Instance.
		*/
		void Create();

		/**
		* @brief Get Extension Requirements.
		*/
		void GetExtensionRequirements();

		/**
		* @brief Check Extension Requirements Satisfied.
		*/
		bool CheckExtensionRequirementsSatisfied();

		/**
		* @brief Get Layer Requirements.
		*/
		void GetLayerRequirements();

		/**
		* @brief Check Layer Requirements Satisfied.
		*/
		bool CheckLayerRequirementsSatisfied();

	private:

		Unit::Instance m_Instance;                                             // @brief This Instance.
		std::vector<const char*> m_ExtensionProperties;                        // @brief Extensions.
		std::vector<const char*> m_LayerProperties;                            // @brief Layers.
		
#ifdef NEPTUNE_DEBUG
		
		Unit::DebugUtilsMessenger m_DebugMessenger;                            // @brief DebugUtilsMessenger.
		
#endif
		
	};

}

#endif