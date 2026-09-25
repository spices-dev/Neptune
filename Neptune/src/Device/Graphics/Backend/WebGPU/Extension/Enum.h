/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_WEBGPU

namespace Neptune::WebGPU {

    /**
    * @brief Enum of Extension.
    */
    enum class EExtension : uint8_t
    {
        TimedWaitAny,                                // @brief TimedWaitAny.
        ShaderSourceSPIRV,                           // @brief ShaderSourceSPIRV.
        MultipleDevicesPerAdapter,                   // @brief MultipleDevicesPerAdapter.
        ReadonlyAndReadwriteStorageTextures,         // @brief ReadonlyAndReadwriteStorageTextures.
        Packed4x8IntegerDotProduct,                  // @brief Packed4x8IntegerDotProduct.
        UnrestrictedPointerParameters,               // @brief UnrestrictedPointerParameters.
        PointerCompositeAccess,                      // @brief PointerCompositeAccess.
        
        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case TimedWaitAny:                              return "TimedWaitAny";
            case ShaderSourceSPIRV:                         return "ShaderSourceSPIRV";
            case MultipleDevicesPerAdapter:                 return "MultipleDevicesPerAdapter";
            case ReadonlyAndReadwriteStorageTextures:       return "ReadonlyAndReadwriteStorageTextures";
            case Packed4x8IntegerDotProduct:                return "Packed4x8IntegerDotProduct";
            case UnrestrictedPointerParameters:             return "UnrestrictedPointerParameters";
            case PointerCompositeAccess:                    return "PointerCompositeAccess";
            
            default:                                        return "NonNamed";
        }
    }

}

#endif