/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_VULKAN

namespace Neptune::Vulkan {

    /**
    * @brief Enum of Layer.
    */
    enum class ELayer : uint8_t
    {
        ApiDump = 0,                 // @brief LunarG ApiDump.
        CrashDiagnostic,             // @brief LunarG CrashDiagnostic.
        GfxReconstruct,              // @brief LunarG GfxReconstruct.
        Monitor,                     // @brief LunarG Monitor.
        ScreenShot,                  // @brief LunarG ScreenShot.
        Validation,                  // @brief Khronos Validation.
        Profiles,                    // @brief Khronos Profiles.
        ShaderObject,                // @brief Khronos ShaderObject.
        Synchronization2,            // @brief Khronos Synchronization2.

        EOSOverlay,                  // @brief Epic EOSOverlay.
        GPUTrace,                    // @brief Nvidia GPUTrace.
        NgfxCapture,                 // @brief Nvidia NgfxCapture.
        Nomad,                       // @brief Nvidia Nomad.
        Optimus,                     // @brief Nvidia Optimus.
        Present,                     // @brief Nvidia Present.
        ShaderDebugger,              // @brief Nvidia ShaderDebugger.
        Capture,                     // @brief RenderDoc Capture.
        GvkRestorePoint,             // @brief Intel GvkRestorePoint.
        GvkStateTracker,             // @brief Intel GvkStateTracker.
        GvkVirtualSwapchain,         // @brief Intel GvkVirtualSwapchain.
        
        SwapChainCapture,            // @brief Neptune SwapChainCapture.

        Count
    };
    
    inline std::string ToString(ELayer e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum ELayer;
        
        switch (e)
        {
            case ApiDump:                    return "ApiDump";
            case CrashDiagnostic:            return "CrashDiagnostic";
            case GfxReconstruct:             return "GfxReconstruct";
            case Monitor:                    return "Monitor";
            case ScreenShot:                 return "ScreenShot";
            case Validation:                 return "Validation";
            case Profiles:                   return "Profiles";
            case ShaderObject:               return "ShaderObject";
            case Synchronization2:           return "Synchronization2";
            case EOSOverlay:                 return "EOSOverlay";
            case GPUTrace:                   return "GPUTrace";
            case NgfxCapture:                return "NgfxCapture";
            case Nomad:                      return "Nomad";
            case Optimus:                    return "Optimus";
            case Present:                    return "Present";
            case ShaderDebugger:             return "ShaderDebugger";
            case Capture:                    return "Capture";
            case GvkRestorePoint:            return "GvkRestorePoint";
            case GvkStateTracker:            return "GvkStateTracker";
            case GvkVirtualSwapchain:        return "GvkVirtualSwapchain";
            case SwapChainCapture:           return "SwapChainCapture";
            default:                         return "NonNamed";
        }
    }

}

#endif