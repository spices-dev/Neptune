/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

namespace Neptune::Vulkan {

    /**
    * @brief Enum of Middleware.
    */
    enum class EMiddleware : uint8_t
    {
        GetPhysicalDeviceProperties,          // @brief GetPhysicalDeviceProperties.
        GetSurfaceCapabilities,               // @brief GetSurfaceCapabilities.
        ImageLayout,                          // @brief ImageLayout.
        Indirect,                             // @brief Indirect.
        QueueSubmit,                          // @brief QueueSubmit.
        Synchronization,                      // @brief Synchronization.
        TimeLine,                             // @brief TimeLine.

        Count
    };

}

#endif