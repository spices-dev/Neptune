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
    
#define DISPATCH(name)                                        \
    if (strcmp(pName, #name) == 0)                            \
    {                                                         \
        return reinterpret_cast<PFN_vkVoidFunction>(name);    \
    }

    /**
    * @brief Instance Dispatch Table(Sample)
    */
    struct InstanceTable
    {
        PFN_vkGetInstanceProcAddr        vkGetInstanceProcAddr;         // @brief PFN_vkGetInstanceProcAddr.
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
        PFN_vkDestroyDevice     vkDestroyDevice;                // @brief PFN_vkDestroyDevice.
        VkPhysicalDevice        vkPhysicalDevice;               // @brief VkPhysicalDevice.
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
        
        /**
        * @brief Constructor Function.
        * 
        * @note This Class not allowed constructor behaves.
        */
        DispatchTable() = delete;
        
        /**
        * @brief Destructor Function.
        * 
        * @note This Class not allowed destructor behaves.
        */
        virtual ~DispatchTable() = delete;
        
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
        
    private:
        
        template <typename T>
        static void* GetKey(T&& handle) { return *reinterpret_cast<void**>(handle); }
        
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
        DISPATCH(vkGetInstanceProcAddr)
        
        DISPATCH(vkCreateInstance)
        DISPATCH(vkDestroyInstance)
        DISPATCH(vkCreateDevice)
        
        PFN_vkGetInstanceProcAddr nextGipa = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            nextGipa = s_InstanceTable.at(GetKey(instance)).vkGetInstanceProcAddr;
        }
        
        return std::invoke(nextGipa, instance, pName);
    }

    template <IsITable ITable, IsDTable DTable>
    inline PFN_vkVoidFunction DispatchTable<ITable, DTable>::vkGetDeviceProcAddr(VkDevice device, const char* pName)
    {
        DISPATCH(vkGetDeviceProcAddr)
        
        DISPATCH(vkDestroyDevice)
        
        PFN_vkGetDeviceProcAddr nextGdpa = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            nextGdpa = s_DeviceTable.at(GetKey(device)).vkGetDeviceProcAddr;
        }

        return std::invoke(nextGdpa, device, pName);
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
        table.vkDestroyInstance            = reinterpret_cast<PFN_vkDestroyInstance>           (std::invoke(nextGipa, *pInstance, "vkDestroyInstance"));
        table.vkCreateDevice               = reinterpret_cast<PFN_vkCreateDevice>              (std::invoke(nextGipa, *pInstance, "vkCreateDevice"));
        table.vkSubmitDebugUtilsMessageEXT = reinterpret_cast<PFN_vkSubmitDebugUtilsMessageEXT>(std::invoke(nextGipa, *pInstance, "vkSubmitDebugUtilsMessageEXT"));
        
        std::unique_lock lock(s_Mutex);
        
        s_InstanceTable.emplace(GetKey(*pInstance), table);
        
        SetLogFunctor([&](LogStream::LogLevel level, const char* message){Log(*pInstance, level, message); });
        
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
        
        PFN_vkCreateDevice nextvkCreateDevice = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
            
            nextvkCreateDevice = s_InstanceTable.at(GetKey(physicalDevice)).vkCreateDevice;
        }
        
        chainInfo->u.pLayerInfo = chainInfo->u.pLayerInfo->pNext;
        
        auto result = std::invoke(nextvkCreateDevice, physicalDevice, pCreateInfo, pAllocator, pDevice);
        
        if (result != VK_SUCCESS)
        {
            return result;
        }
        
        DTable                         table{};
        table.vkGetDeviceProcAddr    = nextGdpa;
        table.vkPhysicalDevice       = physicalDevice;
        table.vkDestroyDevice        = reinterpret_cast<PFN_vkDestroyDevice>(std::invoke(nextGdpa, *pDevice, "vkDestroyDevice"));

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
        PFN_vkSubmitDebugUtilsMessageEXT submit = nullptr;
        
        {
            std::unique_lock lock(s_Mutex);
  
            submit = s_InstanceTable.at(GetKey(instance)).vkSubmitDebugUtilsMessageEXT;
        }

        if (!submit) return;
        
        VkDebugUtilsMessengerCallbackDataEXT    data{};
        data.sType                            = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT;
        data.pMessageIdName                   = "NEPTUNE_swapchain_capture";
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
        
        std::invoke(submit, instance, severity, VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, &data);
    }
}
