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

        m_Life.destructor(m_Handle, m_Life.allocator);
    }
    
    VkResult Instance::CreateInstance(const VkInstanceCreateInfo& info)
    {
        return m_Life.constructor(&info, m_Life.allocator, &m_Handle);
    }
}