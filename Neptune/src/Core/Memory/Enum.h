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
    enum class MemoryEnum : uint8_t
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
    inline const char* ToString(MemoryEnum memory)
    {
        NEPTUNE_PROFILE_ZONE
        
        switch (memory)
        {
            case MemoryEnum::Host:            return "Host";
            case MemoryEnum::Device:          return "Device";
            case MemoryEnum::HostDevice:      return "Host Device";
            case MemoryEnum::Shared:          return "Shared";
            case MemoryEnum::Other:           return "Other";
            default:                          return "Unknown";
        }
    }

}