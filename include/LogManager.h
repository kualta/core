#ifndef CORE_LOGMANAGER_H
#define CORE_LOGMANAGER_H

#include <string>
#include "Singleton.h"


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
    WINDOW,
    DEBUG,
};
enum PASS_INFO {
    SUCCESS,
    NO_INFO,
    FAIL,
};

class LogManager : public Singleton<LogManager> {

public:
    LogManager();

private:
    void LogInfo(const std::string& message, LOG_TYPE logType, PASS_INFO success);
    void LogWarn(const std::string& message, LOG_TYPE logType, PASS_INFO success);
    void LogError(const std::string& message, LOG_TYPE logType, PASS_INFO success);

    std::string PassText(PASS_INFO success);
    std::string TypeText(LOG_TYPE log_type);

    std::string successText_ = "- success";
    std::string failText_ = "- failed";
};


}

#endif //CORE_LOGMANAGER_H
