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
        ApiDump = 0,                 // @brief Validation.
        CrashDiagnostic,             // @brief CrashDiagnostic.
        GfxReconstruct,              // @brief GfxReconstruct.
        Monitor,                     // @brief Monitor.
        ScreenShot,                  // @brief ScreenShot.
        Validation,                  // @brief Validation.
        Profiles,                    // @brief Profiles.
        ShaderObject,                // @brief ShaderObject.
        Synchronization2,            // @brief Synchronization2.

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
            default:                         return "NonNamed";
        }
    }

}

#endif