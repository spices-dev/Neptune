/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

namespace Neptune::Vulkan {

    /**
    * @brief Enum of Extension.
    */
    enum class EExtension : uint8_t
    {
        DescriptorBuffer = 0,                       // @brief DescriptorBuffer.
        DescriptorHeap,                             // @brief DescriptorHeap.
        DeviceFault,                                // @brief DeviceFault.
        MemoryBudget,                               // @brief MemoryBudget.
        HDR,                                        // @brief HDR.
        OpticalFlow,                                // @brief OpticalFlow.
        RayTracing,                                 // @brief RayTracing.
        SwapChain,                                  // @brief SwapChain.
        VideoDecode,                                // @brief VideoDecode.
        VideoEncode,                                // @brief VideoEncode.
        YCrBrConversion,                            // @brief YCrBrConversion.
        Maintenance1,                               // @brief Maintenance1.
        DebugUtils,                                 // @brief DebugUtils.

        Count
    };

}

#endif