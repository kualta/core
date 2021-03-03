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
    void Log(LOG_LEVEL level, const std::string& message, PASS_INFO success);

    void LogInfo(const std::string& message, PASS_INFO success);

    void LogWarn(const std::string& message, PASS_INFO success);

    void LogError(const std::string& message, PASS_INFO success);

}


#endif //INTERFACERS_LOGGER_H
