#ifndef INTERFACERS_LOGGER_H
#define INTERFACERS_LOGGER_H

#include <string>


namespace core {

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



    class Logger {

    public:
        void Log(LOG_LEVEL level, const std::string& message);
        void Log(LOG_LEVEL level, const std::string& message, PASS_INFO success);

    private:
        void LogInfo(const std::string& message, PASS_INFO success);
        void LogWarn(const std::string& message, PASS_INFO success);
        void LogError(const std::string& message, PASS_INFO success);
        std::string AfterText(PASS_INFO success);

        std::string successText = "- success";
        std::string failText = "- failed";

    };
}


#endif //INTERFACERS_LOGGER_H
