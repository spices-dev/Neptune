#include <cstring>
#include <functional>

#include "Core.h"

namespace Neptune::VkLayer {
    
    struct InstanceTable
    {
        PFN_vkVoidFunction vkCreateInstance;
        PFN_vkVoidFunction vkEnumerateInstanceLayerProperties;
        PFN_vkVoidFunction vkEnumerateInstanceExtensionProperties;
        PFN_vkVoidFunction vkGetInstanceProcAddr;
        PFN_vkVoidFunction vkDestroyInstance;
        PFN_vkVoidFunction vkCreateDevice;
    };
    
    inline VkResult vkCreateInstance(
        const VkInstanceCreateInfo* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkInstance* pInstance
    ){
        auto* chainInfo = static_cast<VkLayerInstanceCreateInfo*>(const_cast<void*>(pCreateInfo->pNext));
        
        while (chainInfo && !(chainInfo->sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO && chainInfo->function == VK_LAYER_LINK_INFO))
        {
            chainInfo = static_cast<VkLayerInstanceCreateInfo*>(const_cast<void*>(chainInfo->pNext));
        }
        if (!chainInfo)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        
        auto nextGipa = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
        
        auto nextCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(std::invoke(nextGipa, VK_NULL_HANDLE, "vkCreateInstance"));
        if (!nextCreateInstance)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;

        VkResult result = std::invoke(nextCreateInstance, pCreateInfo, pAllocator, pInstance);
        if (result != VK_SUCCESS)
        {
            return result;
        }
        
        // Initialize Instance Despatch Table.
        
        return VK_SUCCESS;
    }
    
    inline PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char* pName)
    {
        if (strcmp(pName, "vkCreateInstance") == 0)
        {
            return reinterpret_cast<PFN_vkVoidFunction>(vkCreateInstance);
        }
        
        if (!instance) return nullptr;
        
        return nullptr;
    }
    
}