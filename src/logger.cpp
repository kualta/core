#include <logger.h>
#include <string>


namespace core {


    void Log(LOG_LEVEL level, const std::string& message) {
        switch (level) {
            case INFO  : LogInfo(message);
            case WARN  : LogWarn(message);
            case ERROR : LogError(message);
        }
    }

    void LogInfo(const std::string& message) {
        // TODO: Actual info logging
    }

    void LogWarn(const std::string& message) {
        // TODO: Actual warn logging
    }

    void LogError(const std::string& message) {
        // TODO: Actual error logging + reporting
    }

    class Logger {
        // FIXME: why do we need this again?

    public:


    private:


    };

}