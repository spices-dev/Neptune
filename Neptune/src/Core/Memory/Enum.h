/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"

namespace Neptune {

    /**
    * @brief Enum of Memory.
    */
    enum class EMemory : uint8_t
    {
        Host,            // @brief Host RAM
        Device,          // @brief Device VRAM
        HostDevice,      // @brief Host Device RAM
        Shared,          // @brief Shared UMA
        Other,           // @brief Other LAZILY_ALLOCATED_BIT | PROTECTED_BIT
        
        Count
    };
    
    /**
    * @brief Convert MemoryEnum to string.
    *
    * @param[in] memory MemoryEnum.
    *
    * @return Returns string.
    */
    inline const char* ToString(EMemory memory)
    {
        NEPTUNE_PROFILE_ZONE
        
        using enum EMemory;
        
        switch (memory)
        {
            case Host:            return "Host";
            case Device:          return "Device";
            case HostDevice:      return "Host Device";
            case Shared:          return "Shared";
            case Other:           return "Other";
            default:              return "Unknown";
        }
    }

}