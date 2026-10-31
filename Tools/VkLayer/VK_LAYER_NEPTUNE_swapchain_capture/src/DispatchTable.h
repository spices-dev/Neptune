/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/DispatchTable.h"

namespace Neptune::VkLayer {
    
    /**
    * @brief Device Dispatch Table
    */
    struct DeviceTable : public Core::DeviceTable
    {
        PFN_vkCreateSwapchainKHR     vkCreateSwapchainKHR;       // @brief PFN_vkCreateSwapchainKHR.
        PFN_vkDestroySwapchainKHR    vkDestroySwapchainKHR;      // @brief PFN_vkDestroySwapchainKHR.
        PFN_vkQueuePresentKHR        vkQueuePresentKHR;          // @brief PFN_vkQueuePresentKHR.
        PFN_vkGetSwapchainImagesKHR  vkGetSwapchainImagesKHR;    // @brief PFN_vkGetSwapchainImagesKHR.
    };
    
    /**
    * @brief DispatchTable
    */
    class DispatchTable : public Core::DispatchTable<Core::InstanceTable, DeviceTable>
    {
    public:
        
        using Super = This;
        
    public:
        
        /**
        * @brief Constructor Function.
        */
        DispatchTable() = default;
        
        /**
        * @brief Destructor Function.
        */
        ~DispatchTable() override = default;
        
    public:
        
        /**
        * @brief Hook of vkCreateSwapchainKHR.
        * 
        * @param[in] device VkDevice.
        * @param[in] pCreateInfo VkInstanceCreateInfo.
        * @param[in] pAllocator VkAllocationCallbacks.
        * @param[in] pSwapchain VkSwapchainKHR.
        * 
        * @return Returns VkResult.
        */
        static VkResult vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain);
        
        /**
        * @brief Hook of vkDestroySwapchainKHR.
        * 
        * @param[in] device VkDevice.
        * @param[in] swapchain VkSwapchainKHR.
        * @param[in] pAllocator VkAllocationCallbacks.
        * 
        */
        static void vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator);
        
        /**
        * @brief Hook of vkQueuePresentKHR.
        * 
        * @param[in] queue VkQueue.
        * @param[in] pPresentInfo VkPresentInfoKHR.
        * 
        * @return Returns VkResult.
        */
        static VkResult vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo);
    };
    
    /**
    * @brief Get Layer Name.
    * 
    * @return Returns Layer Name.
    */
    template <>
    inline char* DispatchTable::Super::GetName() { static char name[] = "VK_LAYER_NEPTUNE_swapchain_capture"; return name; }
    
    /**
    * @brief Interface of Dispatch Instance Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::Super::InstanceDispatch(const char* pName) { return nullptr; }
        
    /**
    * @brief Interface of Dispatch Device Function.
    * 
    * @param[in] pName Function Name.
    * 
    * @return Returns PFN_vkVoidFunction.
    */
    template <>
    inline PFN_vkVoidFunction DispatchTable::Super::DeviceDispatch(const char* pName)
    {
        using Scope = VkLayer::DispatchTable;
        
        DISPATCH_SCOPE(vkCreateSwapchainKHR)
        DISPATCH_SCOPE(vkDestroySwapchainKHR)
        DISPATCH_SCOPE(vkQueuePresentKHR)
        
        return nullptr;
    }
        
    /**
    * @brief Interface of Get Instance Table.
    * 
    * @param[in] table ITable.
    */
    template <>
    inline void DispatchTable::Super::GetInstanceTable(ITable& table) {}
        
    /**
    * @brief Interface of Get Device Table.
    * 
    * @param[in] table ITable.
    */
    template <>
    inline void DispatchTable::Super::GetDeviceTable(DTable& table)
    {
        EXPLAIN_DEVICE_FN(vkCreateSwapchainKHR)
        EXPLAIN_DEVICE_FN(vkDestroySwapchainKHR)
        EXPLAIN_DEVICE_FN(vkQueuePresentKHR)
        EXPLAIN_DEVICE_FN(vkGetSwapchainImagesKHR)
    }
}
