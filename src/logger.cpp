#include <logger.h>
#include <iostream>
#include <string>


namespace core {


    void Log(LOG_LEVEL level, const std::string& message) {
        switch (level) {
            case INFO  : LogInfo(message, NO_INFO);
            case WARN  : LogWarn(message, NO_INFO);
            case ERR   : LogError(message, NO_INFO);
        }
    }

    void Log(LOG_LEVEL level, const std::string& message, PASS_INFO passInfo) {
        switch (level) {
            case INFO  : LogInfo(message, passInfo);
            case WARN  : LogWarn(message, passInfo);
            case ERR   : LogError(message, passInfo);
        }
    }

    void LogInfo(const std::string& message, PASS_INFO passInfo) {

        std::string afterText;

        switch (passInfo) {
            case NO_INFO : afterText = "";
            case SUCCESS : afterText =
        }

        std::cout << "INFO: " << message << successText << std::endl;
    }

    void LogWarn(const std::string& message, PASS_INFO passInfo) {
        std::cout << "WARN: " << message << std::endl;
    }

    void LogError(const std::string& message, PASS_INFO passInfo) {
        std::cout << "ERROR! " << message << std::endl;
    }

    class Logger {
        // FIXME: why do we need this again?

    public:


    private:


    };

}