/**
* @file IGetPhysicalDeviceProperties.h.
* @brief The IGetPhysicalDeviceProperties Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Middleware {
	
    /**
    * @brief Interface of IGetPhysicalDeviceProperties.
    */
    class IGetPhysicalDeviceProperties
    {
    public:
		
        /**
        * @brief Create IGetPhysicalDeviceProperties.
        * 
        * @param context Context.
        * 
        * @return Returns IGetPhysicalDeviceProperties.
        */
        static UP<IGetPhysicalDeviceProperties> Create(Context& context);
		
        /**
        * @brief Destructor Function.
        */
        virtual ~IGetPhysicalDeviceProperties() = default;
    	
    	/**
		* @brief Interface of GetPhysicalDeviceProperties.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] properties VkPhysicalDeviceProperties2.
		*/
    	virtual void GetProperties(VkPhysicalDevice device, VkPhysicalDeviceProperties2& properties) const = 0;
    };
	
	/**
	* @brief Implement of GetPhysicalDeviceProperties.
	*/
	class GetPhysicalDeviceProperties : public IGetPhysicalDeviceProperties
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		GetPhysicalDeviceProperties() = default;

		/**
		* @brief Destructor Function.
		*/
		~GetPhysicalDeviceProperties() override = default;
		
		/**
		* @brief Interface of GetPhysicalDeviceProperties.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] properties VkPhysicalDeviceProperties2.
		*/
		void GetProperties(VkPhysicalDevice device, VkPhysicalDeviceProperties2& properties) const override;
	};
	
	/**
	* @brief Implement of GetPhysicalDeviceProperties2.
	*/
	class GetPhysicalDeviceProperties2 : public IGetPhysicalDeviceProperties
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		GetPhysicalDeviceProperties2() = default;

		/**
		* @brief Destructor Function.
		*/
		~GetPhysicalDeviceProperties2() override = default;
		
		/**
		* @brief Interface of GetPhysicalDeviceProperties.
		* 
		* @param[in] device VkPhysicalDevice.
		* @param[in] properties VkPhysicalDeviceProperties2.
		*/
		void GetProperties(VkPhysicalDevice device, VkPhysicalDeviceProperties2& properties) const override;
	};
}

#endif