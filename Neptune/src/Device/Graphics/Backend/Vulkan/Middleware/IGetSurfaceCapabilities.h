/**
* @file IGetSurfaceCapabilities.h.
* @brief The IGetSurfaceCapabilities Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan {
	
	class Extensions;
}

namespace Neptune::Vulkan::Middleware {
	
    /**
    * @brief Interface of IGetSurfaceCapabilities.
    */
    class IGetSurfaceCapabilities
    {
    public:
		
        /**
        * @brief Create IGetSurfaceCapabilities.
        * 
        * @param context Context.
        * 
        * @return Returns IGetSurfaceCapabilities.
        */
        static UP<IGetSurfaceCapabilities> Create(const Context& context);
		
    	/**
		* @brief Create IGetSurfaceCapabilities.
		* 
		* @param extensions Extensions.
		* 
		* @return Returns IGetSurfaceCapabilities.
		*/
    	static UP<IGetSurfaceCapabilities> Create(Extensions* extensions);
    	
        /**
        * @brief Destructor Function.
        */
        virtual ~IGetSurfaceCapabilities() = default;
    	
    	/**
		* @brief Interface of GetSurfaceCapabilities.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] surfaceInfo VkPhysicalDeviceSurfaceInfo2KHR.
		* @param[in] surfaceCapabilities VkSurfaceCapabilities2KHR.
		*/
    	virtual void GetCapabilities(VkPhysicalDevice device, const VkPhysicalDeviceSurfaceInfo2KHR& surfaceInfo, VkSurfaceCapabilities2KHR& surfaceCapabilities) const = 0;
    };
	
	/**
	* @brief Implement of GetSurfaceCapabilities.
	*/
	class GetSurfaceCapabilities : public IGetSurfaceCapabilities
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		GetSurfaceCapabilities() = default;

		/**
		* @brief Destructor Function.
		*/
		~GetSurfaceCapabilities() override = default;

		/**
		* @brief Interface of GetSurfaceCapabilities.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] surfaceInfo VkPhysicalDeviceSurfaceInfo2KHR.
		* @param[in] surfaceCapabilities VkSurfaceCapabilities2KHR.
		*/
		void GetCapabilities(VkPhysicalDevice device, const VkPhysicalDeviceSurfaceInfo2KHR& surfaceInfo, VkSurfaceCapabilities2KHR& surfaceCapabilities) const override;
	};
	
	/**
	* @brief Implement of GetSurfaceCapabilities2.
	*/
	class GetSurfaceCapabilities2 : public IGetSurfaceCapabilities
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		GetSurfaceCapabilities2() = default;

		/**
		* @brief Destructor Function.
		*/
		~GetSurfaceCapabilities2() override = default;
		
		/**
		* @brief Interface of GetSurfaceCapabilities.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] surfaceInfo VkPhysicalDeviceSurfaceInfo2KHR.
		* @param[in] surfaceCapabilities VkSurfaceCapabilities2KHR.
		*/
		void GetCapabilities(VkPhysicalDevice device, const VkPhysicalDeviceSurfaceInfo2KHR& surfaceInfo, VkSurfaceCapabilities2KHR& surfaceCapabilities) const override;
	};
}

#endif