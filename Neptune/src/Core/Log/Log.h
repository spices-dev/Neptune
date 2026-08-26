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
        bool IsInitialized() const { return m_IsInitialized; }

        /**
        * @brief Set Initialized state.
        * 
        * @param[in] isInitialized .
        */
        void SetInitialized(bool isInitialized) { m_IsInitialized = isInitialized; }
        
    private:

        /**
        * @brief Boolean of Initialize state.
        */
        bool m_IsInitialized = false;
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
        ~LogStream();

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
}

#ifdef NEPTUNE_DEBUG

// Core log macros
#define NEPTUNE_LOG_CORE(level)    Neptune::LogStream(true,  Neptune::LogStream::LogLevel::level)
// Client log macro
#define NEPTUNE_LOG(level)         Neptune::LogStream(false, Neptune::LogStream::LogLevel::level)

#endif // NEPTUNE_DEBUG

#ifdef NEPTUNE_RELEASE

// Core log macros
#define NEPTUNE_LOG_CORE(level)    Neptune::LogStream(true,  Neptune::LogStream::LogLevel::level)
// Client log macro
#define NEPTUNE_LOG(level)         Neptune::LogStream(false, Neptune::LogStream::LogLevel::level)

#endif // NEPTUNE_RELEASE