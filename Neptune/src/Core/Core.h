/**
* @file Core.h.
* @brief Neptune Core Macro.
* @author Spices.
*/

#pragma once
#include "Memory/Core.h"
#include "Compiler.h"
#include "Log/Log.h"
#include "Debugger/Profiler/ProfilerC.h"
#include "MetaProperty.h"

namespace Neptune {

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
}