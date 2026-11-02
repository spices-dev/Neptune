/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

#include <cstdint>

namespace Neptune {

    /**
    * @brief Enum of Infrastructure.
    */
    enum class EInfrastructure : uint8_t
    {
        InstanceTable = 0,                       // @brief InstanceTable.
        DeviceTable,                             // @brief DeviceTable.

        Count
    };

}
