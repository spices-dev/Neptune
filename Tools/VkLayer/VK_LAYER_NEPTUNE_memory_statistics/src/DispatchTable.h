/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/DispatchTable.h"
#include "Enum.h"

namespace Neptune {
    
    /**
    * @brief DispatchTable
    */
    using DispatchTable = Vulkan::DispatchTable<EInfrastructure>;
    
    /**
    * @brief Get Layer Name.
    * 
    * @return Returns Layer Name.
    */
    template <>
    inline char* DispatchTable::GetName() { static char name[] = "VK_LAYER_NEPTUNE_memory_statistics"; return name; }
    
    /**
    * @brief Interface of Dispatch Instance Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::InstanceDispatch(const char* pName) { return nullptr; }
        
    /**
    * @brief Interface of Dispatch Device Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::DeviceDispatch(const char* pName) { return nullptr; }
}
