#include <core/Logger.h>
#include <iostream>


namespace core {


// TODO: Simplify logging syntax
// TODO: Add time/date stamps to logs
Logger::Logger() {
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
std::string Logger::PassText(PASS_INFO success) {

    std::string afterText;

    switch (success) {
        case NO_INFO : afterText = "";
        case FAIL    : afterText = "- failed";
        case SUCCESS : afterText = "- success";
    }

    return afterText;
}
std::string Logger::TypeText(LOG_TYPE log_type) {

    std::string preText;

    switch (log_type) {
        case GENERAL : preText = "|"; break;
        case NETWORK : preText = "|NET|"; break;
        case INTERNAL: preText = "|CORE|"; break;
        case PHYSICS : preText = "|PHYS|"; break;
        case DEBUG   : preText = "|DEBUG|"; break;
        case WINDOW  : preText = "|WINDOW|"; break;
        case RENDER  : preText = "|RENDER|"; break;
    }

    return preText;
}


}