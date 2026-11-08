/**
* @file Core.h.
* @brief Neptune VkLayer Core Macro.
* @author Spices.
*/

#pragma once
#include "Log.h"

#include <memory>
#include <cassert>

namespace Neptune {

#define NONE_COPY(T)                    \
    T(const T&) = delete;               \
    T& operator=(const T&) = delete;    \
    
#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __attribute__((visibility("default")))
#endif
    
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
    
}