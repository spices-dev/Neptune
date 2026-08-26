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
        SamplerYcbcrConversion,                     // @brief SamplerYcbcrConversion.
        Maintenance1,                               // @brief Maintenance1.
        DebugUtils,                                 // @brief DebugUtils.

        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case DescriptorBuffer:           return "DescriptorBuffer";
            case DescriptorHeap:             return "DescriptorHeap";
            case DeviceFault:                return "DeviceFault";
            case MemoryBudget:               return "MemoryBudget";
            case HDR:                        return "HDR";
            case OpticalFlow:                return "OpticalFlow";
            case RayTracing:                 return "RayTracing";
            case SwapChain:                  return "SwapChain";
            case VideoDecode:                return "VideoDecode";
            case VideoEncode:                return "VideoEncode";
            case SamplerYcbcrConversion:     return "SamplerYcbcrConversion";
            case Maintenance1:               return "Maintenance1";
            case DebugUtils:                 return "DebugUtils";
            default:                         return "NonNamed";
        }
    }

}

#endif