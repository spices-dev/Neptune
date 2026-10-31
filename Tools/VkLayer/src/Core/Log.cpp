/**
* @file Log.cpp.
* @brief The Log Class Implementation.
* @author Spices.
*/

#include "Log.h"
#include "DispatchTable.h"

namespace Neptune::VkLayer {

    namespace {
        
        std::function<void(LogStream::LogLevel, const char*)> s_LogFn = nullptr;  // @brief Log Functor.
    }
    
    void SetLogFunctor(const std::function<void(LogStream::LogLevel, const char*)>& fn)
    {
        s_LogFn = fn;
    }
    
    LogStream::~LogStream()
    {
        const std::string msg = m_Stream.str();
        
        if (s_LogFn) std::invoke(s_LogFn, m_Level, msg.c_str());
    }
}