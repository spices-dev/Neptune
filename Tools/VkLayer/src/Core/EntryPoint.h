/**
* @file EntryPoint.h.
* @brief EntryPoint Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/Core.h"

extern "C" {

    /**
    * @brief Export vkGetInstanceProcAddr.
    * 
    * @param[in] instance VkInstance.
    * @param[in] pName Functor Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    DLL_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char* pName);

    /**
    * @brief Export vkGetDeviceProcAddr.
    * 
    * @param[in] device VkDevice.
    * @param[in] pName Functor Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    DLL_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char* pName);

    /**
    * @brief Export vkNegotiateLoaderLayerInterfaceVersion.
    * 
    * @param[in] pVersionStruct VkNegotiateLayerInterface.
    * 
    * @return Returns VkResult.
    */
    DLL_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkNegotiateLoaderLayerInterfaceVersion(VkNegotiateLayerInterface* pVersionStruct)
    {
        static constexpr uint32_t LayerInterfaceVersion = 2u;
        
        if (!pVersionStruct || pVersionStruct->sType != LAYER_NEGOTIATE_INTERFACE_STRUCT)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        pVersionStruct->loaderLayerInterfaceVersion  = LayerInterfaceVersion;
        pVersionStruct->pfnGetInstanceProcAddr       = vkGetInstanceProcAddr;
        pVersionStruct->pfnGetDeviceProcAddr         = vkGetDeviceProcAddr;
        pVersionStruct->pfnGetPhysicalDeviceProcAddr = nullptr;
        
        return VK_SUCCESS;
    }

}