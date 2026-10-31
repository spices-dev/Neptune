/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/DispatchTable.h"

namespace Neptune::VkLayer {
    
    using DispatchTable = Core::DispatchTable<Core::InstanceTable, Core::DeviceTable>;
    
}
