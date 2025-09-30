#include "logging.hpp"

namespace sabre
{
    LoggingLevel Logging::_level = LoggingLevel::NOTSET;

    void Logger::log(const LoggingLevel level, const std::string &message)
    {
        Logging::log(level, _name, message);
    }

    void Logger::debug(const std::string &message)
    {
        log(LoggingLevel::DEBUG, message);
    }

    void Logger::info(const std::string &message)
    {
        log(LoggingLevel::INFO, message);
    }

    void Logger::notice(const std::string &message)
    {
        log(LoggingLevel::NOTICE, message);
    }

    void Logger::warning(const std::string &message)
    {
        log(LoggingLevel::WARNING, message);
    }

    void Logger::error(const std::string &message)
    {
        log(LoggingLevel::ERROR, message);
    }

    void Logger::critical(const std::string &message)
    {
        log(LoggingLevel::CRITICAL, message);
    }

    void Logger::alert(const std::string &message)
    {
        log(LoggingLevel::ALERT, message);
    }

    void Logger::emergency(const std::string &message)
    {
        log(LoggingLevel::EMERGENCY, message);
    }

    void Logging::set_level(LoggingLevel level)
    {
        _level = level;
    }

    LoggingLevel Logging::get_level()
    {
        return _level;
    }

    Logger::Logger(const std::string &name) : _name(name) {}
    std::forward_list<LogHandlerSharedPtr> Logging::_handlers;

    void Logging::log(const LoggingLevel level, const std::string &logger_name,
                      const std::string &message)
    {
        if (level <= _level)
            for (const auto &handler : _handlers)
                handler->handle_log(level, logger_name, message);
    }

    void Logging::add_handler(LogHandlerSharedPtr handler)
    {
        _handlers.push_front(handler);
    }

    void Logging::remove_handler(LogHandlerSharedPtr handler)
    {
        _handlers.remove(handler);
    }
} // namespace sabre