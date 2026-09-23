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
        Maintenance4,                               // @brief Maintenance4.
        Maintenance5,                               // @brief Maintenance5.
        DebugUtils,                                 // @brief DebugUtils.
        BufferDeviceAddress,                        // @brief BufferDeviceAddress.
        DescriptorIndexing,                         // @brief DescriptorIndexing.
        Vulkan13,                                   // @brief Vulkan13.
        Portability,                                // @brief Portability.
        Queue,                                      // @brief Queue.
        LayerSetting,                               // @brief LayerSetting.
        DynamicRendering,                           // @brief DynamicRendering.
        ExternalMemoryHost,                         // @brief ExternalMemoryHost.
        CopyMemoryIndirect,                         // @brief CopyMemoryIndirect.
        DeviceGeneratedCommands,                    // @brief DeviceGeneratedCommands.
        GetPhysicalDeviceProperties2,               // @brief GetPhysicalDeviceProperties2.
        PageableDeviceLocalMemory,                  // @brief PageableDeviceLocalMemory.
        GetSurfaceCapabilities2,                    // @brief GetSurfaceCapabilities2.
        CreateRenderPass2,                          // @brief CreateRenderPass2.
        DynamicRenderingLocalRead,                  // @brief DynamicRenderingLocalRead.
        ScalarBlockLayout,                          // @brief ScalarBlockLayout.
        TimelineSemaphore,                          // @brief TimelineSemaphore.
        Synchronization2,                           // @brief Synchronization2.
        PresentTiming,                              // @brief PresentTiming.
        UnifiedImageLayouts,                        // @brief UnifiedImageLayouts.
        MeshShader,                                 // @brief MeshShader.

        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case DescriptorBuffer:                return "DescriptorBuffer";
            case DescriptorHeap:                  return "DescriptorHeap";
            case DeviceFault:                     return "DeviceFault";
            case MemoryBudget:                    return "MemoryBudget";
            case HDR:                             return "HDR";
            case OpticalFlow:                     return "OpticalFlow";
            case RayTracing:                      return "RayTracing";
            case SwapChain:                       return "SwapChain";
            case VideoDecode:                     return "VideoDecode";
            case VideoEncode:                     return "VideoEncode";
            case SamplerYcbcrConversion:          return "SamplerYcbcrConversion";
            case Maintenance1:                    return "Maintenance1";
            case Maintenance4:                    return "Maintenance4";
            case DebugUtils:                      return "DebugUtils";
            case BufferDeviceAddress:             return "BufferDeviceAddress";
            case DescriptorIndexing:              return "DescriptorIndexing";
            case Vulkan13:                        return "Vulkan13";
            case Portability:                     return "Portability";
            case Queue:                           return "Queue";
            case LayerSetting:                    return "LayerSetting";
            case DynamicRendering:                return "DynamicRendering";
            case ExternalMemoryHost:              return "ExternalMemoryHost";
            case CopyMemoryIndirect:              return "CopyMemoryIndirect";
            case DeviceGeneratedCommands:         return "DeviceGeneratedCommands";
            case GetPhysicalDeviceProperties2:    return "GetPhysicalDeviceProperties2";
            case PageableDeviceLocalMemory:       return "PageableDeviceLocalMemory";
            case GetSurfaceCapabilities2:         return "GetSurfaceCapabilities2";
            case CreateRenderPass2:               return "CreateRenderPass2";
            case DynamicRenderingLocalRead:       return "DynamicRenderingLocalRead";
            case ScalarBlockLayout:               return "ScalarBlockLayout";
            case TimelineSemaphore:               return "TimelineSemaphore";
            case Synchronization2:                return "Synchronization2";
            case PresentTiming:                   return "PresentTiming";
            case UnifiedImageLayouts:             return "UnifiedImageLayouts";
            case MeshShader:                      return "MeshShader";
            default:                              return "NonNamed";
        }
    }

}

#endif