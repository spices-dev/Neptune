/**
* @file Log.h
* @brief The Log Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/NonCopyable.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <cstdlib>

namespace Neptune {

    /**
    * @brief Log Class defines log behaves.
    */
    class Log : public NonCopyable
    {
    public:
        
        /**
        * @brief Get this instance.
        * 
        * @return Returns this instance.
        */
        static const std::unique_ptr<Log>& Get();

        /**
        * @brief Reset this instance.
        */
        static void Reset();

        /**
        * @brief Constructor Function.
        */
        Log() = default;

        /**
        * @brief Destructor Function.
        */
        virtual ~Log() = default;

        virtual void CoreTrace   (const std::string& msg) const = 0;
        virtual void CoreInfo    (const std::string& msg) const = 0;
        virtual void CoreWarn    (const std::string& msg) const = 0;
        virtual void CoreError   (const std::string& msg) const = 0;
        virtual void CoreCritical(const std::string& msg) const = 0;

        virtual void ClientTrace   (const std::string& msg) const = 0;
        virtual void ClientInfo    (const std::string& msg) const = 0;
        virtual void ClientWarn    (const std::string& msg) const = 0;
        virtual void ClientError   (const std::string& msg) const = 0;
        virtual void ClientCritical(const std::string& msg) const = 0;

        /**
        * @brief Get Initialized state.
        * 
        * @return Returns Initialized state.
        */
        static bool IsInitialized();

        /**
        * @brief Set Initialized state.
        * 
        * @param[in] isInitialized .
        */
        static void SetInitialized(bool isInitialized);
    };
    
    /**
    * @brief LogStream Class.
    */
    class LogStream
    {
    public:

        /**
        * @brief Severity Levels
        */
        enum class LogLevel
        {
            T,     // @brief Trace
            I,     // @brief Info
            W,     // @brief Warning
            E,     // @brief Error
            C      // @brief CRITICAL
        };
        
        /**
        * @brief Constructor Function.
        * 
        * @param[in] core true in Engine.
        * @param[in] level Severity Level of the message.
        */
        LogStream(bool core, LogLevel level)
            : m_IsCore(core)
            , m_Level(level)
        {}

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
        
        bool m_IsCore;                 // @brief True in Engine Scope.
        LogLevel m_Level;              // @brief Severity Level.
        std::ostringstream m_Stream;   // @brief Log Stream.
        
    };

    template <LogStream::LogLevel Level>
    constexpr bool IsLogLevelEnabled() 
    {
#ifdef NEPTUNE_DEBUG
        return Level >= LogStream::LogLevel::T;
#endif

#ifdef NEPTUNE_RELEASE
        return Level >= LogStream::LogLevel::I;
#endif
        
    }
}

// Cross-platform debug break
#ifdef NEPTUNE_DEBUG
#ifdef _MSC_VER
#define NEPTUNE_BREAK __debugbreak(); std::abort(); 
#elif defined(__GNUC__) || defined(__clang__)
#include <csignal>
#define NEPTUNE_BREAK raise(SIGTRAP); std::abort(); 
#else
#define NEPTUNE_BREAK std::abort(); 
#endif
#endif

#ifdef NEPTUNE_RELEASE
#define NEPTUNE_BREAK
#endif

// Core log macros
#define NEPTUNE_LOG_CORE(level)                                              \
    if constexpr (!Neptune::IsLogLevelEnabled<Neptune::LogStream::LogLevel::level>()) {} \
    else Neptune::LogStream(true, Neptune::LogStream::LogLevel::level)

// Client log macro
#define NEPTUNE_LOG(level)                                                   \
    if constexpr (!Neptune::IsLogLevelEnabled<Neptune::LogStream::LogLevel::level>()) {} \
    else Neptune::LogStream(false, Neptune::LogStream::LogLevel::level)