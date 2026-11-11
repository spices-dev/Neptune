/**
* @file IImageLayout.h.
* @brief The IImageLayout Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Device/Graphics/Backend/Vulkan/Core.h"
#include "Context.h"

namespace Neptune::Vulkan::Middleware {
	
	using IIImageLayout = IMiddleware<class IImageLayout, EMiddleware::ImageLayout>;
	
    /**
    * @brief Interface of ImageLayout.
    */
    class IImageLayout : public Middleware
    {
    public:
		
        /**
        * @brief Create IImageLayout.
        * 
        * @param context Context.
        * 
        * @return Returns IImageLayout.
        */
        static UP<IImageLayout> Create(const Context& context);
		
        /**
        * @brief Destructor Function.
        */
    	~IImageLayout() override = default;

        /**
        * @brief Interface of Transform VkImageLayout to VkImageLayout.
        * 
        * @param[in] layout VkImageLayout.
        * 
        * @return Returns VkImageLayout.
        */
        virtual VkImageLayout From(VkImageLayout layout) const = 0;
    };
	
	/**
	* @brief Implement of ImageLayout.
	*/
	class ImageLayout : public IImageLayout
	{
	public:

		/**
		* @brief Constructor Function.
		* 
		* @param[in] dynamicRendering .
		*/
		explicit ImageLayout(bool dynamicRendering) : m_DynamicRendering(dynamicRendering) {}

		/**
		* @brief Destructor Function.
		*/
		~ImageLayout() override = default;

		/**
		* @brief Interface of Transform VkImageLayout to VkImageLayout.
		* 
		* @param[in] layout VkImageLayout.
		* 
		* @return Returns VkImageLayout.
		*/
		VkImageLayout From(VkImageLayout layout) const override;
	
	private:
		
		bool m_DynamicRendering = false;    // @brief Extension: DynamicRendering.
	};
	
	/**
	* @brief Implement of ImageLayout2.
	*/
	class ImageLayout2 : public IImageLayout
	{
	public:

		/**
		* @brief Constructor Function.
		*/
		ImageLayout2() = default;

		/**
		* @brief Destructor Function.
		*/
		~ImageLayout2() override = default;

		/**
		* @brief Interface of Transform VkImageLayout to VkImageLayout.
		* 
		* @param[in] layout VkImageLayout.
		* 
		* @return Returns VkImageLayout.
		*/
		VkImageLayout From(VkImageLayout layout) const override;
	};
}

#endif