/**
* @file Extensions.h.
* @brief The Extensions Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Infrastructure.h"
#include "Device/Graphics/Backend/Vulkan/Extension/Context.h"

namespace Neptune {
	
	class Window;
}

namespace Neptune::Vulkan {

	using IExtensions = IInfrastructure<class Extensions, EInfrastructure::Extensions>;

	/**
	* @brief Vulkan::Extensions Class.
	* This class defines the Vulkan::Extensions behaves.
	*/
	class Extensions : public Infrastructure
	{
	public:

		/**
		* @brief Constructor Function.
		*
		* @param[in] context Context.
		* @param[in] e EInfrastructure.
		* @param[in] window Window.
		*/
		Extensions(Context& context, EInfrastructure e, const Window* window = nullptr);

		/**
		* @brief Destructor Function.
		*/
		~Extensions() override = default;
		
		/**
		* @brief Copy from this.
		* 
		* @return Returns copied Extensions.
		*/
		UP<Extensions> Copy() const;
		
		/**
		* @brief Copy from extensions.
		* 
		* @param[in] extensions Extensions.
		*/
		void CopyFrom(const UP<Extensions>& extensions);
		
		/**
		* @brief Get Extension::EContext.
		* 
		* @return Returns Extension::EContext.
		*/
		const SP<Extension::EContext<EExtension>>& GetContext() const { return m_Context; }
		
		/**
		* @brief Get Extension::EContext.
		*
		* @return Returns Extension::EContext.
		*/
		SP<Extension::EContext<EExtension>>& GetContext() { return m_Context; }
		
		/**
		* @brief Build Device Feature Chain.
		* 
		* @param[in] pNext pNext Chain.
		*/
		void BuildFeatureChain(void** pNext);
		
		/**
		* @brief Build Device Feature Chain(Contain Once).
		*
		* @param[in] pNext pNext Chain.
		*/
		void BuildFeatureChainWithoutRepeat(void** pNext);

		/**
		* @brief Build Device Property Chain.
		* 
		* @param[in] pNext pNext Chain.
		*/
		void BuildPropertyChain(void** pNext);
		
		/**
		* @brief Build Device Surface Capability Chain.
		* 
		* @param[in] pNext pNext Chain.
		*/
		void BuildSurfaceCapabilityChain(void** pNext);
		
		/**
		* @brief Build Device Queue Chain.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] surface VkSurfaceKHR.
		* 
		* @return Returns Required Chain.
		*/
		std::unordered_set<VkQueueFlagBits> BuildQueueChain(const VkPhysicalDevice& device, const VkSurfaceKHR& surface) const;

    private:
        
        /**
        * @brief Create Extension.
        */
        void Create();
		
    private:
    
        SP<Extension::EContext<EExtension>> m_Context; // @brief This EContext.
		const Window* m_Window;                        // @brief Window. 
	};
	
}

#endif