/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/DispatchTable.h"

namespace Neptune::VkLayer {
    
    /**
    * @brief DispatchTable
    */
    using DispatchTable = Core::DispatchTable<Core::InstanceTable, Core::DeviceTable>;
    
    /**
    * @brief Get Layer Name.
    * 
    * @return Returns Layer Name.
    */
    template <>
    inline char* DispatchTable::GetName() { static char name[] = "VK_LAYER_NEPTUNE_sample"; return name; }
    
    /**
    * @brief Interface of Dispatch Instance Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::InstanceDispatch(const char* pName) { NEPTUNE_LOG_CORE(I) << "InstanceDispatch"; return nullptr; }
        
    /**
    * @brief Interface of Dispatch Device Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::DeviceDispatch(const char* pName) { NEPTUNE_LOG_CORE(I) << "DeviceDispatch"; return nullptr; }
        
    /**
    * @brief Interface of Get Instance Table.
    * 
    * @param[in] table ITable.
    */
    template <>
    inline void DispatchTable::GetInstanceTable(ITable& table) { NEPTUNE_LOG_CORE(I) << "GetInstanceTable"; }
        
    /**
    * @brief Interface of Get Device Table.
    * 
    * @param[in] table ITable.
    */
    template <>
    inline void DispatchTable::GetDeviceTable(DTable& table) { NEPTUNE_LOG_CORE(I) << "GetDeviceTable"; }
}
