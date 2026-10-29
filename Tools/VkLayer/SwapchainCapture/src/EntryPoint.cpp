#include "Instance.h"
#include "Device.h"

DLL_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface* pVersionStruct)
{
    if (!pVersionStruct || pVersionStruct->sType != LAYER_NEGOTIATE_INTERFACE_STRUCT)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    pVersionStruct->loaderLayerInterfaceVersion  = 2;
    pVersionStruct->pfnGetInstanceProcAddr       = Neptune::VkLayer::vkGetInstanceProcAddr;
    pVersionStruct->pfnGetDeviceProcAddr         = Neptune::VkLayer::vkGetDeviceProcAddr;
    pVersionStruct->pfnGetPhysicalDeviceProcAddr = nullptr;
    
    return VK_SUCCESS;
}

DLL_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName)
{
    return Neptune::VkLayer::vkGetInstanceProcAddr(instance, pName);
}

DLL_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName)
{
    return Neptune::VkLayer::vkGetDeviceProcAddr(device, pName);
}