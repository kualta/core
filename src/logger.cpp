#include <logger.h>
#include <iostream>
#include <string>


namespace core {



// TODO: Add time/date stamps to logs
void Logger::Log(LOG_LEVEL level, const std::string& message) {
    switch (level) {
        case INFO  : Logger::LogInfo(message, NO_INFO);
        case WARN  : Logger::LogWarn(message, NO_INFO);
        case ERR   : Logger::LogError(message, NO_INFO);
    }
}

void Logger::Log(LOG_LEVEL level, const std::string& message, PASS_INFO success) {
    switch (level) {
        case INFO  : Logger::LogInfo(message, success);
        case WARN  : Logger::LogWarn(message, success);
        case ERR   : Logger::LogError(message, success);
    }
}

void Logger::LogInfo(const std::string& message, PASS_INFO passInfo) {
    std::cout << "INFO: " << message << AfterText(passInfo) << std::endl;
}

void Logger::LogWarn(const std::string& message, PASS_INFO passInfo) {
    std::cout << "WARN: " << message << AfterText(passInfo) << std::endl;
}

void Logger::LogError(const std::string& message, PASS_INFO passInfo) {
    std::cout << "ERROR! " << message << AfterText(passInfo) << std::endl;
}

std::string Logger::AfterText(PASS_INFO success) {

    std::string afterText;

    switch (success) {
        case NO_INFO : afterText = "";
        case SUCCESS : afterText = successText;
        case FAIL    : afterText = failText;
    }

    return afterText;
}

Logger *Logger::GetInstance() {

  return &instance;

}



}