/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#ifdef NP_GRAPHICS_DIRECT3D12

namespace Neptune::Direct3D12 {

    /**
    * @brief Enum of Extension.
    */
    enum class EExtension : uint8_t
    {
        RenderPass = 0,                             // @brief RenderPass.

        Count
    };
    
    inline std::string ToString(EExtension e)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EExtension;
        
        switch (e)
        {
            case RenderPass:                      return "RenderPass";
            default:                              return "NonNamed";
        }
    }

}

#endif