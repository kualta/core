#ifndef INTERFACERS_LOGGER_H
#define INTERFACERS_LOGGER_H

#include <string>


namespace core {


enum LOG_LEVEL {
    INFO,
    WARN,
    ERR,
};
enum LOG_TYPE {
    GENERAL,
    PHYSICS,
    NETWORK,
    RENDER,
    DEBUG,
};
enum PASS_INFO {
    SUCCESS,
    NO_INFO,
    FAIL,
};

class Logger {

public:
    Logger();
    Logger(Logger& other) = delete;             /// Since Logger is a singleton, it must not be cloneable and assignable
    void operator=(const Logger &) = delete;    ///

    void Log(LOG_LEVEL level, const std::string& message, LOG_TYPE logType = GENERAL, PASS_INFO success = NO_INFO);
    static Logger* GetInstance();

private:
    void LogInfo(const std::string& message, LOG_TYPE logType, PASS_INFO success);
    void LogWarn(const std::string& message, LOG_TYPE logType, PASS_INFO success);
    void LogError(const std::string& message, LOG_TYPE logType, PASS_INFO success);

    std::string AfterText(PASS_INFO success);
    std::string PreText(LOG_TYPE log_type);

    std::string successText_ = "- success";
    std::string failText_ = "- failed";

    static Logger* logger_;
};


}

#endif //INTERFACERS_LOGGER_H
