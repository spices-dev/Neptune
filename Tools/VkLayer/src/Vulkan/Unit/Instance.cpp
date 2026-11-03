/**
* @file Instance.cpp.
* @brief The Instance Class Implementation.
* @author Spices.
*/

#include "Instance.h"

namespace Neptune::Vulkan::Unit {

    Instance::~Instance()
    {
        if (!m_Handle) return;

        std::invoke(m_Life.destructor, m_Handle, m_Life.allocator);
    }
    
    void Instance::CreateInstance(const VkInstanceCreateInfo& info)
    {
        VULKAN_CHECK(std::invoke(m_Life.constructor, &info, m_Life.allocator, &m_Handle))
    }
}