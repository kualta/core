#ifndef INTERFACERS_LOGGER_H
#define INTERFACERS_LOGGER_H

#include <string>


namespace core {

    std::string successText = "- success";

    enum LOG_LEVEL {
        INFO,
        WARN,
        ERR,
    };

    enum PASS_INFO {
        SUCCESS,
        FAIL,
        NO_INFO
    };

    void Log(LOG_LEVEL level, const std::string& message);
    void Log(LOG_LEVEL level, const std::string& message, PASS_INFO passInfo);

    void LogInfo(const std::string& message);

    void LogWarn(const std::string& message);

    void LogError(const std::string& message);

}


#endif //INTERFACERS_LOGGER_H
