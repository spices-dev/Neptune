/**
* @file Surface.cpp.
* @brief The Surface Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_GRAPHICS_VULKAN

#include "Surface.h"

namespace Neptune::Vulkan::Unit {

	Surface::~Surface()
	{
		NEPTUNE_PROFILE_ZONE

		if (!m_Handle || !m_Instance) return;

		vkDestroySurfaceKHR(m_Instance, m_Handle, GetAllocator());
	}

	void Surface::SetInstance(VkInstance instance)
	{
		NEPTUNE_PROFILE_ZONE

		m_Instance = instance;
	}
	
	void Surface::CreateDisplaySurface(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR& info)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Instance = instance;
		
		VULKAN_CHECK(vkCreateDisplayPlaneSurfaceKHR(instance, &info, GetAllocator(), &m_Handle))
	}
	
	void Surface::CreateHeadlessSurface(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT& info)
	{
		NEPTUNE_PROFILE_ZONE
		
		m_Instance = instance;
		
		VULKAN_CHECK(vkCreateHeadlessSurfaceEXT(instance, &info, GetAllocator(), &m_Handle))
	}
}

#endif