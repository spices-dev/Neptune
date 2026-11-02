/**
* @file EntryPoint.cpp.
* @brief The EntryPoint Implementation.
* @author Spices.
*/

#include "Core/EntryPoint.h"
#include "DispatchTable.h"

PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return Neptune::DispatchTable::vkGetInstanceProcAddr(instance, pName);
}

PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
    return Neptune::DispatchTable::vkGetDeviceProcAddr(device, pName);
}