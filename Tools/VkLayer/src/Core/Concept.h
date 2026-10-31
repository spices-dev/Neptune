/**
* @file Concept.h.
* @brief The Concept Definitions.
* @author Spices.
*/

#pragma once

namespace Neptune::VkLayer::Core {
    
    /**
    * @brief Concept: Is Instance Table.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsITable = requires(T t) {
        std::is_same_v<PFN_vkGetInstanceProcAddr,        decltype(T::vkGetInstanceProcAddr)>;         // @brief PFN_vkGetInstanceProcAddr.
        std::is_same_v<VkInstance,                       decltype(T::vkInstance)>;                    // @brief VkInstance.
        std::is_same_v<PFN_vkDestroyInstance,            decltype(T::vkDestroyInstance)>;             // @brief PFN_vkDestroyInstance.
        std::is_same_v<PFN_vkCreateDevice,               decltype(T::vkCreateDevice)>;                // @brief PFN_vkCreateDevice.
        std::is_same_v<PFN_vkSubmitDebugUtilsMessageEXT, decltype(T::vkSubmitDebugUtilsMessageEXT)>;  // @brief PFN_vkSubmitDebugUtilsMessageEXT.
    };
    
    /**
    * @brief Concept: Is Device Table.
    * 
    * @tparam T .
    */
    template<typename T>
    concept IsDTable = requires(T t) {
        std::is_same_v<PFN_vkGetDeviceProcAddr, decltype(T::vkGetDeviceProcAddr)>;          // @brief PFN_vkGetDeviceProcAddr.
        std::is_same_v<VkPhysicalDevice,        decltype(T::vkPhysicalDevice)>;             // @brief VkPhysicalDevice.
        std::is_same_v<VkDevice,                decltype(T::vkDevice)>;                     // @brief VkDevice.
        std::is_same_v<PFN_vkDestroyDevice,     decltype(T::vkDestroyDevice)>;              // @brief PFN_vkDestroyDevice.
    };
    
}