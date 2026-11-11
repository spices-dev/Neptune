/**
* @file Middleware.h.
* @brief The Middleware Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

#include "Core/Core.h"
#include "Core/Container/Empty.h"
#include "Device/Graphics/Backend/Vulkan/Infrastructure/Infrastructure.h"

namespace Neptune::Vulkan::Middleware {
    
    /**
    * @brief Vulkan::Middleware Class.
    */
    using Middleware = Container::Empty;
}

#endif