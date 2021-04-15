#include <core/Logger.h>
#include <iostream>


namespace core {


// TODO: Simplify logging syntax
// TODO: Add time/date stamps to logs
string Logger::PassText(PASS_INFO success) {

   string afterText;

    switch (success) {
        case NO_INFO : afterText = ""; break;
        case FAIL    : afterText = "- failed"; break;
        case SUCCESS : afterText = "- success"; break;
    }

    return afterText;
}
string Logger::LevelText(LOG_LEVEL level) {

    string afterText;

    switch (level) {
        case ERR : afterText = "ERROR! "; break;
        case WARN : afterText = "WARN: "; break;
        case INFO : afterText = ""; break;
        case DEBUG : afterText = ""; break;
    }

    return afterText;
}
string Logger::TypeText(LOG_TYPE log_type) {

    string preText;

    switch (log_type) {
        case GENERAL : preText = "        "; break;
        case NETWORK : preText = "|NET|   "; break;
        case INTERNAL: preText = "|CORE|  "; break;
        case PHYSICS : preText = "|PHYS|  "; break;
        case WINDOW  : preText = "|WINDOW|"; break;
        case RENDER  : preText = "|RENDER|"; break;
    }

    return preText;
}
string Logger::TimeNow() {
    // TODO: Implement timestamp
    return "23:23:23.141";
}

void Logger::LogInfo(const std::string &message, LOG_TYPE logType) {
    std::cout << TypeText(logType) << " " << message << std::endl;
}
void Logger::LogWarn(const std::string& message, LOG_TYPE logType) {
    std::cout << TypeText(logType) << " WARN: " << message << std::endl;
}
void Logger::LogError(const std::string& message, LOG_TYPE logType) {
    std::cout << TypeText(logType) << " ERROR! " << message << std::endl;
}
void Logger::LogMessage(const std::string &message) {
    std::cout << message << std::endl;
}
Logger::~Logger() {
}
Log Logger::Log(LOG_LEVEL level, LOG_TYPE type) {
    switch (level) {
        case   ERR: return core::Log(std::cout, ERR, type);
        case  WARN: return core::Log(std::cout, WARN, type);
        case  INFO: return core::Log(std::cout, INFO, type);
        case DEBUG: return core::Log(std::cout, DEBUG, type);
    }
}
string Logger::GetLogEntryText(LOG_TYPE type, LOG_LEVEL level) {
    return "- " + TimeNow() + " " + TypeText(type) + " " + LevelText(level);
}

} // namespace core