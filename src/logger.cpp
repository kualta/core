#include <logger.h>
#include <iostream>
#include <string>


namespace core {


    void Log(LOG_LEVEL level, const std::string& message) {
        switch (level) {
            case INFO  : LogInfo(message);
            case WARN  : LogWarn(message);
            case ERR : LogError(message);
        }
    }

    void LogInfo(const std::string& message) {
        std::cout << "INFO: " << message << std::endl;
        // TODO: Actual info logging
    }

    void LogWarn(const std::string& message) {
        std::cout << "WARN: " << message << std::endl;
        // TODO: Actual warn logging
    }

    void LogError(const std::string& message) {
        std::cout << "ERROR! " << message << std::endl;
        // TODO: Actual error logging + reporting
    }

    class Logger {
        // FIXME: why do we need this again?

    public:


    private:


    };

}