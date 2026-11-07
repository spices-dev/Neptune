/**
* @file Log.h
* @brief The Log Class Definitions.
* @author Spices.
*/

#pragma once
#include <iostream>
#include <sstream>
#include <functional>

namespace Neptune::Vulkan {
    
    /**
    * @brief LogStream Class.
    */
    class LogStream
    {
    public:

        /**
        * @brief Severity Levels
        */
        enum class LogLevel : uint8_t
        {
            T,     // @brief Trace
            I,     // @brief Info
            W,     // @brief Warning
            E,     // @brief Error
            C,     // @brief CRITICAL
            
            Count,
        };
        
        /**
        * @brief Constructor Function.
        * 
        * @param[in] level Severity Level of the message.
        */
        LogStream(LogLevel level): m_Level(level) {}

        /**
        * @brief Destructor Function.
        */
        virtual ~LogStream();

        /**
        * @brief Receive log stream.
        * 
        * @tparam T streamed value.
        * @param[in] value Value to append.
        * 
        * @return Returns this
        */
        template<typename T>
        LogStream& operator<<(const T& value)
        {
            m_Stream << value;
            
            return *this;
        }

    private:
        
        LogLevel m_Level;              // @brief Severity Level.
        std::ostringstream m_Stream;   // @brief Log Stream.
    };

    /**
    * @brief Set Log Functor.
    * 
    * @param[in] fn Functor.
    */
    void SetLogFunctor(const std::function<void(LogStream::LogLevel, const char*)>& fn);
    
    template <LogStream::LogLevel Level>
    constexpr bool IsLogLevelEnabled() 
    {
#ifdef NEPTUNE_DEBUG
        return Level >= LogStream::LogLevel::T;
#elif defined(NEPTUNE_RELEASE)
        return Level >= LogStream::LogLevel::I;
#else
        return Level >= LogStream::LogLevel::T;
#endif
        
    }
}

// Core log macros
#define NEPTUNE_LOG_CORE(level)                                              \
    if constexpr (!Neptune::Vulkan::IsLogLevelEnabled<Neptune::Vulkan::LogStream::LogLevel::level>()) {} \
    else Neptune::Vulkan::LogStream(Neptune::Vulkan::LogStream::LogLevel::level)