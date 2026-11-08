/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Vulkan/DispatchTable.h"
#include "Infrastructure/SwapChain.h"
#include "Infrastructure/CommandBuffer.h"
#include "LayerSetting.h"
#include "Enum.h"

namespace Neptune {
    
    /**
    * @brief DispatchTable
    */
    class DispatchTable : public Vulkan::DispatchTable<EInfrastructure>
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
    * @brief Interface of InitContext.
    */
    template <>
    inline void DispatchTable::Super::InitContext()
    {
        s_Context.Registry<Vulkan::ISwapChain>();
        s_Context.Registry<Vulkan::ICommandBuffer>();
    }
        
    /**
    * @brief Interface of Init Settings.
    * 
    * @param[in] setting Resource::LayerSetting.
    * 
    * @return Returns VkResult.
    */
    template <>
    inline VkResult DispatchTable::Super::InitSettings(UP<Vulkan::Resource::LayerSetting>& setting)
    {
        auto data = CreateSP<Settings>();
        
        VULKAN_CHECK(setting->GetValue("save_path", data->save_path, std::string("not find")))
        VULKAN_CHECK(setting->GetValue("capture_every_n_frames", data->capture_every_n_frames, 60u))
        VULKAN_CHECK(setting->GetValue("max_captures", data->max_captures, 0u))
        
        setting->SetSetting(data);
        
        return VK_SUCCESS;
    }
    
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
        using Scope = Neptune::DispatchTable;
        
        DISPATCH_SCOPE(vkCreateSwapchainKHR)
        DISPATCH_SCOPE(vkDestroySwapchainKHR)
        DISPATCH_SCOPE(vkQueuePresentKHR)
        
        return nullptr;
    }
}
