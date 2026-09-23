/**
* @file Image.cpp.
* @brief The Image Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Image.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/DebugUtilsObject.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/MemoryAllocator.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/PhysicalDevice.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Device.h"

namespace Neptune::Vulkan::Resource {

	void Image::SetImage(Unit::Image::Handle image)
	{
		NEPTUNE_PROFILE_ZONE

		m_Image.SetHandle(image);

		DEBUGUTILS_SETOBJECTNAME(m_Image, "Image")
	}

	void Image::CreateImage(const VkImageCreateInfo& info, VkMemoryPropertyFlags properties)
	{
		NEPTUNE_PROFILE_ZONE

		m_Format                     = info.format;
		m_LayerCount                 = info.arrayLayers;
		m_Width                      = info.extent.width;
		m_Height                     = info.extent.height;
		 
		GetContext().Has<IMemoryAllocator>() ? 
		m_Image.CreateImage(GetContext().Get<IMemoryAllocator>()->Handle(), info, properties) : 
		m_Image.CreateImage(GetContext().Get<IPhysicalDevice>()->Handle(), GetContext().Get<IDevice>()->Handle(), info, properties);

		DEBUGUTILS_SETOBJECTNAME(m_Image, "Image")
	}

	void Image::CreateImageView(const VkImageViewCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		assert(m_Image.GetHandle());

		m_ImageView.CreateImageView(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_ImageView, "ImageView")
	}

	void Image::CreateSampler(const VkSamplerCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_ImageSampler.CreateSampler(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, "Sampler")
	}

	void Image::CreateSamplerYcbcrConversion(const VkSamplerYcbcrConversionCreateInfo& info)
	{
		NEPTUNE_PROFILE_ZONE

		m_Conversion.CreateSamplerYcbcrConversion(GetContext().Get<IDevice>()->Handle(), info);

		DEBUGUTILS_SETOBJECTNAME(m_Conversion, "SamplerYcbcrConversion")
	}

	void Image::SetName(const std::string& name) const
	{
		NEPTUNE_PROFILE_ZONE

		DEBUGUTILS_SETOBJECTNAME(m_Image,        name + "Image")
		DEBUGUTILS_SETOBJECTNAME(m_ImageView,    name + "ImageView")
		DEBUGUTILS_SETOBJECTNAME(m_ImageSampler, name + "Sampler")
		DEBUGUTILS_SETOBJECTNAME(m_Conversion,   name + "SamplerYcbcrConversion")
	}
}

#endif