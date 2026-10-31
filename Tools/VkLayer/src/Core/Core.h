/**
* @file Core.h.
* @brief Neptune VkLayer Core Macro.
* @author Spices.
*/

#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/vk_layer.h>
#include <memory>
#include <cassert>

namespace Neptune::VkLayer {

#define NONE_COPY(T)                    \
    T(const T&) = delete;               \
    T& operator=(const T&) = delete;    \
    
    /**
    * @brief SharedPointer.
    *
    * @tparam T Type.
    */
    template<typename T>
    using SP = std::shared_ptr<T>;

    /**
    * @brief Create shared pointer.
    *
    * @tparam T Type.
    * 
    * @param[in] args Arguments.
    */
    template<typename T, typename ...Args>
    SP<T> CreateSP(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    /**
    * @brief WeakPointer.
    *
    * @tparam T Type.
    */
    template<typename T>
    using WP = std::weak_ptr<T>;

    /**
    * @brief UniquePointer.
    *
    * @tparam T Type.
    */
    template<typename T>
    using UP = std::unique_ptr<T>;

    /**
    * @brief Create unique pointer.
    *
    * @tparam T Type.
    * 
    * @param[in] args Arguments.
    */
    template<typename T, typename ...Args>
    UP<T> CreateUP(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
    
#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif
    
    constexpr uint32_t LayerInterfaceVersion = 2u;   // @brief Layer Interface Version.
    
    #define VULKAN_CHECK(expr)  { auto expr_value = expr; assert(expr_value == VK_SUCCESS); }
    
}