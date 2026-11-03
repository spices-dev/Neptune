/**
* @file Enum.h.
* @brief The Enum Class Definitions.
* @author Spices.
*/

#pragma once

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
