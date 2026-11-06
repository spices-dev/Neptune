/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Vulkan/Infrastructure/InstanceTable.h"
#include "Vulkan/Infrastructure/DeviceTable.h"
#include "Core/Log.h"

#include <mutex>
#include <shared_mutex>
#include <unordered_map>

namespace Neptune::Vulkan {
    
#define DISPATCH_SCOPE(name)                                                                 \
    if (strcmp(pName, #name) == 0)                                                           \
    {                                                                                        \
        return reinterpret_cast<PFN_vkVoidFunction>(Scope::name);                            \
    }
    
#define ACCURE_INSTANCE_FN(name, handle) \
    const PFN_##name name = s_Context.template Get<Vulkan::IInstanceTable>()->Get(GetKey(handle)).name;
    
#define ACCURE_DEVICE_FN(name, handle) \
    const PFN_##name name = s_Context.template Get<Vulkan::IDeviceTable>()->Get(GetKey(handle)).name;
    
#define ACCURE_DEVICE(name, handle) \
    const Vulkan::DeviceTable& name = s_Context.template Get<Vulkan::IDeviceTable>()->Get(GetKey(handle));
    
    /**
    * @brief DispatchTable
    * 
    * @tparam E EInfrastructure
    */
    template<typename E>
    class DispatchTable
    {
    public:
        
        using This    = DispatchTable;
        using Context = Context<Infrastructure, E>;
        
    public:
        
        /**
        * @brief Constructor Function.
        */
        DispatchTable() = default;
        
        /**
        * @brief Destructor Function.
        */
        virtual ~DispatchTable() = default;
        
        NONE_COPY(DispatchTable)
        
        /**
        * @brief Hook of vkGetInstanceProcAddr.
        * 
        * @param[in] instance VkInstance.
        * @param[in] pName Functor Name.
        * 
        * @return Returns PFN_vkVoidFunction.
        */
        static PFN_vkVoidFunction vkGetInstanceProcAddr(VkInstance instance, const char* pName);
        
        /**
        * @brief Hook of vkGetDeviceProcAddr.
        * 
        * @param[in] device VkDevice.
        * @param[in] pName Functor Name.
        * 
        * @return Returns PFN_vkVoidFunction.
        */
        static PFN_vkVoidFunction vkGetDeviceProcAddr(VkDevice device, const char* pName);
        
    protected:
        
        /**
        * @brief Get Handle Key.
        * 
        * @param[in] handle Handle.
        * 
        * @return Returns Handle Key.
        */
        template <typename T>
        static void* GetKey(T&& handle) { return *reinterpret_cast<void**>(std::forward<T>(handle)); }
        
    private:
        
        /**
        * @brief Hook of vkCreateInstance.
        * 
        * @param[in] pCreateInfo VkInstanceCreateInfo.
        * @param[in] pAllocator VkAllocationCallbacks.
        * @param[in] pInstance VkInstance.
        * 
        * @return Returns VkResult.
        */
        static VkResult vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance);
        
        /**
        * @brief Hook of vkDestroyInstance.
        * 
        * @param[in] instance VkInstance.
        * @param[in] pAllocator VkAllocationCallbacks.
        */
        static void vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator);
        
        /**
        * @brief Hook of vkCreateDevice.
        * 
        * @param[in] physicalDevice VkPhysicalDevice.
        * @param[in] pCreateInfo VkInstanceCreateInfo.
        * @param[in] pAllocator VkAllocationCallbacks.
        * @param[in] pDevice VkDevice.
        * 
        * @return Returns VkResult.
        */
        static VkResult vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice);
        
        /**
        * @brief Hook of vkDestroyDevice.
        * 
        * @param[in] device VkDevice.
        * @param[in] pAllocator VkAllocationCallbacks.
        */
        static void vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);
        
        /**
        * @brief Log to DebugUtils.
        * 
        * @param[in] instance VkInstance.
        * @param[in] level LogStream::LogLevel.
        * @param[in] message .
        */
        static void Log(VkInstance instance, LogStream::LogLevel level, const char* message);
        
    private:
        
        /**
        * @brief Interface of Get Layer Name.
        * 
        * @return Returns Layer Name.
        */
        static char* GetName() { static char name[] = ""; return name; }
        
        /**
        * @brief Interface of InitContext.
        */
        static void InitContext() {}
        
        /**
        * @brief Interface of Dispatch Instance Function.
        * 
        * @param[in] pName Function Name.
        * 
        * @return Returns PFN_vkVoidFunction.
        */
        static PFN_vkVoidFunction InstanceDispatch(const char* pName) { return nullptr; }
        
        /**
        * @brief Interface of Dispatch Device Function.
        * 
        * @param[in] pName Function Name.
        * 
        * @return Returns PFN_vkVoidFunction.
        */
        static PFN_vkVoidFunction DeviceDispatch(const char* pName) { return nullptr; }
        
    private:
        
        /**
        * @brief Interface of Get Instance Table.
        * 
        * @param[in] table InstanceTable.
        */
        static void GetInstanceTable(UP<InstanceTable>& table);
        
        /**
        * @brief Interface of Get Device Table.
        * 
        * @param[in] table DeviceTable.
        */
        static void GetDeviceTable(UP<DeviceTable>& table);
        
        /**
        * @brief Init Table Context.
        */
        static void InitTableContext();
        
    protected:
        
        static Context s_Context;   // @brief Dispatch Table Context.
    };

    template<typename E>
    typename DispatchTable<E>::Context DispatchTable<E>::s_Context;

    template<typename E>
    inline PFN_vkVoidFunction DispatchTable<E>::vkGetInstanceProcAddr(VkInstance instance, const char* pName)
    {
        using Scope = This;
        
        InitTableContext();
        
        DISPATCH_SCOPE(vkGetInstanceProcAddr)
        
        DISPATCH_SCOPE(vkCreateInstance)
        DISPATCH_SCOPE(vkDestroyInstance)
        DISPATCH_SCOPE(vkCreateDevice)
        
        if (auto* fn = InstanceDispatch(pName))
        {
            return fn;
        }
        
        ACCURE_INSTANCE_FN(vkGetInstanceProcAddr, instance)
        
        return std::invoke(vkGetInstanceProcAddr, instance, pName);
    }

    template<typename E>
    inline PFN_vkVoidFunction DispatchTable<E>::vkGetDeviceProcAddr(VkDevice device, const char* pName)
    {
        using Scope = This;
        
        DISPATCH_SCOPE(vkGetDeviceProcAddr)
        
        DISPATCH_SCOPE(vkDestroyDevice)
        
        if (auto* fn = DeviceDispatch(pName))
        {
            return fn;
        }

        ACCURE_DEVICE_FN(vkGetDeviceProcAddr, device)

        return std::invoke(vkGetDeviceProcAddr, device, pName);
    }

    template<typename E>
    inline VkResult DispatchTable<E>::vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
    {
        auto* chainInfo = static_cast<VkLayerInstanceCreateInfo*>(const_cast<void*>(pCreateInfo->pNext));
        
        while (chainInfo && !(chainInfo->sType == VK_STRUCTURE_TYPE_LOADER_INSTANCE_CREATE_INFO && chainInfo->function == VK_LAYER_LINK_INFO))
        {
            chainInfo = static_cast<VkLayerInstanceCreateInfo*>(const_cast<void*>(chainInfo->pNext));
        }
        
        if (!chainInfo)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        
        auto vkGetInstanceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
        
        auto vkCreateInstance  = reinterpret_cast<PFN_vkCreateInstance>(std::invoke(vkGetInstanceProcAddr, VK_NULL_HANDLE, "vkCreateInstance"));
        
        if (!vkCreateInstance)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
        
        auto unit = CreateUP<Unit::Instance>();
    
        {
            unit->SetHandle(*pInstance);
        
            unit->SetLife({ vkCreateInstance, nullptr, pAllocator });
    
            unit->CreateInstance(*pCreateInfo);
    
            *pInstance = unit->GetHandle();
            
            auto vkDestroyInstance = reinterpret_cast<PFN_vkDestroyInstance>(std::invoke(vkGetInstanceProcAddr, *pInstance, "vkDestroyInstance"));
            
            unit->SetLife({ vkCreateInstance, vkDestroyInstance, pAllocator });
        }
        
        auto table = CreateUP<InstanceTable>();;
        
        {
            table->m_Instance            = std::move(unit);
            table->vkGetInstanceProcAddr = vkGetInstanceProcAddr;
    
            GetInstanceTable(table);
        }
        
        {
            auto instance = table->Handle();
        
            SetLogFunctor([=](LogStream::LogLevel level, const char* message) { Log(instance, level, message); });
        
            s_Context.template Get<IInstanceTable>()->Registry(GetKey(instance), std::move(table));
        }
        
        return VK_SUCCESS;
    }

    template <typename E>
    void DispatchTable<E>::GetInstanceTable(UP<InstanceTable>& table)
    {
        
#define EXPLAIN_INSTANCE_FN(name)                             \
    table->name = reinterpret_cast<PFN_##name>(std::invoke(table->vkGetInstanceProcAddr, table->Handle(), #name));
        
        EXPLAIN_INSTANCE_FN(vkCreateDevice)
        EXPLAIN_INSTANCE_FN(vkSubmitDebugUtilsMessageEXT)
        
#undef EXPLAIN_INSTANCE_FN
        
    }

    template <typename E>
    inline void DispatchTable<E>::vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
    {
        s_Context.template Get<IInstanceTable>()->UnRegistry(GetKey(instance));
    }

    template <typename E>
    inline VkResult DispatchTable<E>::vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
    {
        auto* chainInfo = static_cast<VkLayerDeviceCreateInfo*>(const_cast<void*>(pCreateInfo->pNext));
        
        while (chainInfo && !(chainInfo->sType == VK_STRUCTURE_TYPE_LOADER_DEVICE_CREATE_INFO && chainInfo->function == VK_LAYER_LINK_INFO))
        {
            chainInfo = static_cast<VkLayerDeviceCreateInfo*>(const_cast<void*>(chainInfo->pNext));
        }
        
        if (!chainInfo)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }
        
        auto vkGetDeviceProcAddr = chainInfo->u.pLayerInfo->pfnNextGetDeviceProcAddr;
        
        chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
    
        ACCURE_INSTANCE_FN(vkCreateDevice, physicalDevice)
        
        auto unit = CreateUP<Unit::Device>();
        
        {
            unit->SetHandle(*pDevice);
        
            unit->SetLife({ vkCreateDevice, nullptr, pAllocator });
        
            unit->CreateDevice(physicalDevice, *pCreateInfo);
        }
        
        {
            *pDevice = unit->GetHandle();
        
            auto vkDestroyDevice = reinterpret_cast<PFN_vkDestroyDevice>(std::invoke(vkGetDeviceProcAddr, *pDevice, "vkDestroyDevice"));
        
            unit->SetLife({ vkCreateDevice, vkDestroyDevice, pAllocator });
        }
        
        auto table = CreateUP<DeviceTable>();
        
        {
            table->m_Device            = std::move(unit);
            table->vkGetDeviceProcAddr = vkGetDeviceProcAddr;
            table->vkPhysicalDevice    = physicalDevice;
        
            GetDeviceTable(table);
        }
        
        {
            auto device = table->Handle();
        
            s_Context.template Get<IDeviceTable>()->Registry(GetKey(device), std::move(table));
        }
        
        return VK_SUCCESS;
    }

    template <typename E>
    void DispatchTable<E>::GetDeviceTable(UP<DeviceTable>& table)
    {
        
#define EXPLAIN_DEVICE_FN(name)                             \
    table->name = reinterpret_cast<PFN_##name>(std::invoke(table->vkGetDeviceProcAddr, table->Handle(), #name));
        
        EXPLAIN_DEVICE_FN(vkCreateSwapchainKHR)
        EXPLAIN_DEVICE_FN(vkDestroySwapchainKHR)
        EXPLAIN_DEVICE_FN(vkQueuePresentKHR)
        EXPLAIN_DEVICE_FN(vkGetSwapchainImagesKHR)
        EXPLAIN_DEVICE_FN(vkCreateCommandPool)
        EXPLAIN_DEVICE_FN(vkDestroyCommandPool)
        EXPLAIN_DEVICE_FN(vkAllocateCommandBuffers)
        EXPLAIN_DEVICE_FN(vkFreeCommandBuffers)
        EXPLAIN_DEVICE_FN(vkBeginCommandBuffer)
        EXPLAIN_DEVICE_FN(vkEndCommandBuffer)
        EXPLAIN_DEVICE_FN(vkQueueSubmit)
        EXPLAIN_DEVICE_FN(vkDeviceWaitIdle)
        EXPLAIN_DEVICE_FN(vkCreateSemaphore)
        EXPLAIN_DEVICE_FN(vkDestroySemaphore)
        
#undef EXPLAIN_DEVICE_FN
        
    }
    
    template <typename E>
    inline void DispatchTable<E>::vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
    {
        s_Context.template Get<IDeviceTable>()->UnRegistry(GetKey(device));
    }

    template <typename E>
    void DispatchTable<E>::InitTableContext()
    {
        static std::once_flag flag;
            
        std::call_once(flag, []()
        {
            s_Context.template Registry<IInstanceTable>();
            s_Context.template Registry<IDeviceTable>();
                
            InitContext();
        });
    }
    
    template <typename E>
    void DispatchTable<E>::Log(VkInstance instance, LogStream::LogLevel level, const char* message)
    {
        ACCURE_INSTANCE_FN(vkSubmitDebugUtilsMessageEXT, instance)
        
        if (!vkSubmitDebugUtilsMessageEXT) return;
        
        VkDebugUtilsMessengerCallbackDataEXT    data{};
        data.sType                            = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
        data.pMessageIdName                   = GetName();
        data.pMessage                         = message;

        VkDebugUtilsMessageSeverityFlagBitsEXT severity;
        
        switch (level)
        {
            case LogStream::LogLevel::C : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; break;
            case LogStream::LogLevel::E : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT; break;
            case LogStream::LogLevel::W : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT; break;
            case LogStream::LogLevel::I : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT; break;
            case LogStream::LogLevel::T : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT; break;
            default:                      severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT; break;
        }

        std::invoke(vkSubmitDebugUtilsMessageEXT, instance, severity, VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, &data);
    }
}