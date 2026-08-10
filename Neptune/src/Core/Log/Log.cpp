/**
* @file Log.cpp.
* @brief The Log Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"
#include "Core/Core.h"
#include "Log.h"
#include "LogImpl.h"

namespace Neptune {

    namespace {
        
        UP<Log> s_Log = nullptr;
    }
    
    const UP<Log>& Log::Get()
    {
        NEPTUNE_PROFILE_ZONE

        if(!s_Log)
        {
            s_Log = CreateUP<LogImpl>();
        }

        return s_Log;
    }

    void Log::Reset()
    {
        NEPTUNE_PROFILE_ZONE

        s_Log.reset();
    }

    LogStream::~LogStream()
    {
        NEPTUNE_PROFILE_ZONE
        
        const std::string msg = m_Stream.str();
        const auto& log    = Log::Get();
        
        if (!log->IsInitialized())
        {
            std::cout << msg << std::endl;
            return;
        }

        if (m_IsCore)
        {
            switch (m_Level)
            {
                case LogLevel::T:    log->CoreTrace(msg);    break;
                case LogLevel::I:    log->CoreInfo(msg);     break;
                case LogLevel::W:    log->CoreWarn(msg);     break;
                case LogLevel::E:    log->CoreError(msg);    break;
                case LogLevel::C:    log->CoreCritical(msg); break;
                default:             log->CoreTrace(msg);    break;
            }
        }
        else
        {
            switch (m_Level)
            {
                case LogLevel::T:     log->ClientTrace(msg);    break;
                case LogLevel::I:     log->ClientInfo(msg);     break;
                case LogLevel::W:     log->ClientWarn(msg);     break;
                case LogLevel::E:     log->ClientError(msg);    break;
                case LogLevel::C:     log->ClientCritical(msg); break;
                default:              log->CoreTrace(msg);      break;
            }
        }
    }
}