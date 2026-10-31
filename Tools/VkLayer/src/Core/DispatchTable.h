/**
* @file DispatchTable.h.
* @brief The DispatchTable Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core.h"
#include "Concept.h"
#include "Log.h"

#include <mutex>
#include <unordered_map>

namespace Neptune::VkLayer::Core {
    
#define DISPATCH_SCOPE(name)                                                 \
    if (strcmp(pName, #name) == 0)                                           \
    {                                                                        \
        return reinterpret_cast<PFN_vkVoidFunction>(Scope::name);            \
    }
    
#define EXPLAIN_INSTANCE_FN(name)                             \
    table.name = reinterpret_cast<PFN_##name>(std::invoke(table.vkGetInstanceProcAddr, table.vkInstance, #name));
    
#define EXPLAIN_DEVICE_FN(name)                               \
    table.name = reinterpret_cast<PFN_##name>(std::invoke(table.vkGetDeviceProcAddr, table.vkDevice, #name));

#define ACCURE_INSTANCE_FN(name, handle)                              \
    PFN_##name name = nullptr;                                        \
                                                                      \
    {                                                                 \
        std::unique_lock lock(s_Mutex);                               \
                                                                      \
        name = s_InstanceTable.at(GetKey(handle)).name;               \
    } 
    
#define ACCURE_DEVICE_FN(name, handle)                                \
    PFN_##name name = nullptr;                                        \
                                                                      \
    {                                                                 \
        std::unique_lock lock(s_Mutex);                               \
                                                                      \
        name = s_DeviceTable.at(GetKey(handle)).name;                 \
    } 
    
    /**
    * @brief Instance Dispatch Table(Sample)
    */
    struct InstanceTable
    {
        PFN_vkGetInstanceProcAddr        vkGetInstanceProcAddr;         // @brief PFN_vkGetInstanceProcAddr.
        VkInstance                       vkInstance;                    // @brief VkInstance.
        PFN_vkDestroyInstance            vkDestroyInstance;             // @brief PFN_vkDestroyInstance.
        PFN_vkCreateDevice               vkCreateDevice;                // @brief PFN_vkCreateDevice.
        PFN_vkSubmitDebugUtilsMessageEXT vkSubmitDebugUtilsMessageEXT;  // @brief PFN_vkSubmitDebugUtilsMessageEXT
    };
    
    /**
    * @brief Device Dispatch Table(Sample)
    */
    struct DeviceTable
    {
        PFN_vkGetDeviceProcAddr vkGetDeviceProcAddr;            // @brief PFN_vkGetDeviceProcAddr.
        VkPhysicalDevice        vkPhysicalDevice;               // @brief VkPhysicalDevice.
        VkDevice                vkDevice;                       // @brief VkDevice.
        PFN_vkDestroyDevice     vkDestroyDevice;                // @brief PFN_vkDestroyDevice.
    };
    
    /**
    * @brief DispatchTable
    * 
    * @tparam ITable IsITable.
    * @tparam DTable IsDTable.
    */
    template<IsITable ITable, IsDTable DTable>
    class DispatchTable
    {
    public:
        
        using This   = DispatchTable;
        using ITable = ITable;
        using DTable = DTable;
        
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
        
        /**
        * @brief Get Layer Name.
        * 
        * @return Returns Layer Name.
        */
        static char* GetName() { static char name[] = ""; return name; }
        
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
        
        /**
        * @brief Interface of Get Instance Table.
        * 
        * @param[in] table ITable.
        */
        static void GetInstanceTable(ITable& table) {}
        
        /**
        * @brief Interface of Get Device Table.
        * 
        * @param[in] table DTable.
        */
        static void GetDeviceTable(DTable& table) {}
        
    protected:
        
        static std::unordered_map<void*, ITable> s_InstanceTable;   // @brief Instance Dispatch Table.
        static std::unordered_map<void*, DTable> s_DeviceTable;     // @brief Device Dispatch Table.
        static std::mutex                        s_Mutex;           // @brief This Mutex.
    };

    template <IsITable ITable, IsDTable DTable>
    std::unordered_map<void*, ITable> DispatchTable<ITable, DTable>::s_InstanceTable;
    
    template <IsITable ITable, IsDTable DTable>
    std::unordered_map<void*, DTable> DispatchTable<ITable, DTable>::s_DeviceTable;
    
    template <IsITable ITable, IsDTable DTable>
    std::mutex DispatchTable<ITable, DTable>::s_Mutex;

    template <IsITable ITable, IsDTable DTable>
    inline PFN_vkVoidFunction DispatchTable<ITable, DTable>::vkGetInstanceProcAddr(VkInstance instance, const char* pName)
    {
        using Scope = This;
        
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

    template <IsITable ITable, IsDTable DTable>
    inline PFN_vkVoidFunction DispatchTable<ITable, DTable>::vkGetDeviceProcAddr(VkDevice device, const char* pName)
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

    template <IsITable ITable, IsDTable DTable>
    inline VkResult DispatchTable<ITable, DTable>::vkCreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
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
        
        auto nextGipa = chainInfo->u.pLayerInfo->pfnNextGetInstanceProcAddr;
        
        auto nextvkCreateInstance = reinterpret_cast<PFN_vkCreateInstance>(std::invoke(nextGipa, VK_NULL_HANDLE, "vkCreateInstance"));
        
        if (!nextvkCreateInstance)
        {
            return VK_ERROR_INITIALIZATION_FAILED;
        }

        chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;

        auto result = std::invoke(nextvkCreateInstance, pCreateInfo, pAllocator, pInstance);
        
        if (result != VK_SUCCESS)
        {
            return result;
        }
        
        ITable                               table{};
        table.vkGetInstanceProcAddr        = nextGipa;
        table.vkInstance                   = *pInstance;

        EXPLAIN_INSTANCE_FN(vkDestroyInstance)
        EXPLAIN_INSTANCE_FN(vkCreateDevice)
        EXPLAIN_INSTANCE_FN(vkSubmitDebugUtilsMessageEXT)
        
        GetInstanceTable(table);
        
        std::unique_lock lock(s_Mutex);
        
        auto instance = *pInstance;
        
        s_InstanceTable.emplace(GetKey(instance), table);
        
        SetLogFunctor([=](LogStream::LogLevel level, const char* message){ Log(instance, level, message); });
        
        return VK_SUCCESS;
    }

    template <IsITable ITable, IsDTable DTable>
    inline void DispatchTable<ITable, DTable>::vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
    {
        auto* key = GetKey(instance);

        PFN_vkDestroyInstance next = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            next = s_InstanceTable.at(key).vkDestroyInstance;
            
            s_InstanceTable.erase(key);
        }
        
        std::invoke(next, instance, pAllocator);
    }

    template <IsITable ITable, IsDTable DTable>
    inline VkResult DispatchTable<ITable, DTable>::vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
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
        
        PFN_vkGetDeviceProcAddr nextGdpa = chainInfo->u.pLayerInfo->pfnNextGetDeviceProcAddr;
        
        ACCURE_INSTANCE_FN(vkCreateDevice, physicalDevice)
        
        chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
        
        auto result = std::invoke(vkCreateDevice, physicalDevice, pCreateInfo, pAllocator, pDevice);
        
        if (result != VK_SUCCESS)
        {
            return result;
        }
        
        DTable                         table{};
        table.vkGetDeviceProcAddr    = nextGdpa;
        table.vkPhysicalDevice       = physicalDevice;
        table.vkDevice               = *pDevice;
        
        EXPLAIN_DEVICE_FN(vkDestroyDevice)
        
        GetDeviceTable(table);

        {
            std::unique_lock lock(s_Mutex);
            
            s_DeviceTable.emplace(GetKey(*pDevice), table);
        }
        
        return VK_SUCCESS;
    }

    template <IsITable ITable, IsDTable DTable>
    inline void DispatchTable<ITable, DTable>::vkDestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
    {
        auto* key = GetKey(device);
        
        PFN_vkDestroyDevice next = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            next = s_DeviceTable.at(key).vkDestroyDevice;
            
            s_DeviceTable.erase(key);
        }

        std::invoke(next, device, pAllocator);
    }

    template <IsITable ITable, IsDTable DTable>
    void DispatchTable<ITable, DTable>::Log(VkInstance instance, LogStream::LogLevel level, const char* message)
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
            case LogStream::LogLevel::C : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            case LogStream::LogLevel::E : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            case LogStream::LogLevel::W : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
            case LogStream::LogLevel::I : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
            case LogStream::LogLevel::T : severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
            default:                      severity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        }
        
        std::invoke(vkSubmitDebugUtilsMessageEXT, instance, severity, VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, &data);
    }
}
