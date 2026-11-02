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
}