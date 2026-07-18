/**
* @file LogImpl.h
* @brief The LogImpl Class Definitions.
* @author Spices.
*/

#pragma once
#include "Core/Core.h"
#include "Log.h"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE // This Macro must be defined.
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Neptune {

    /**
    * @brief Log Class defines log behaves.
    */
    class LogImpl : public Log
    {
    public:

        /**
        * @brief Constructor Function.
        */
        LogImpl();

        /**
        * @brief Destructor Function.
        */
        ~LogImpl() override;

        void CoreTrace   (const std::string& msg) const override;
        void CoreInfo    (const std::string& msg) const override;
        void CoreWarn    (const std::string& msg) const override;
        void CoreError   (const std::string& msg) const override;
        void CoreCritical(const std::string& msg) const override;

        void ClientTrace   (const std::string& msg) const override;
        void ClientInfo    (const std::string& msg) const override;
        void ClientWarn    (const std::string& msg) const override;
        void ClientError   (const std::string& msg) const override;
        void ClientCritical(const std::string& msg) const override;

    private:

        /**
        * @brief Engine Stage Logger.
        */
        UP<spdlog::logger> m_CoreLogger;

        /**
        * @brief Game Stage Logger.
        */
        UP<spdlog::logger> m_ClientLogger;
    };
}