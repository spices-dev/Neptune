/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Implementation.
* @author Spices.
*/

#include "Core/EntryPoint.h"
#include "DispatchTable.h"

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return Neptune::DispatchTable::vkGetInstanceProcAddr(instance, pName);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
    return Neptune::DispatchTable::vkGetDeviceProcAddr(device, pName);
}