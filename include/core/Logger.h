#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include "Essentials.h"
#include "Singleton.h"
#include "Object.h"
#include "ObjectTag.h"

#include <ostream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <utility>

#ifndef LOG_HERE
#   ifdef CORE_LOG_FULL_PATH
#       define LOG_HERE LogPlace { true, __FILE__, __FUNCTION__, __LINE__ }
#   else
#       define LOG_HERE LogPlace { true, __FILENAME__, __FUNCTION__, __LINE__ }
#   endif
#endif

#ifndef WARN_HERE
#   define WARN_HERE LogLevel::WARN, LOG_HERE
#endif

#ifndef ERR_HERE
#   define ERR_HERE LogLevel::ERR, LOG_HERE
#endif

#ifndef INFO_HERE
#   define INFO_HERE LogLevel::INFO, LOG_HERE
#endif

#ifndef DEBUG_HERE
#   define DEBUG_HERE LogLevel::DEBUG, LOG_HERE
#endif

#ifndef NEW_LINE
#   define NEW_LINE string('\n') + string(16, ' ') + string(' |')
#endif

namespace core {

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERR,
};
enum PassInfo {
    SUCCESS,
    NO_INFO,
    FAIL,
};

struct LogPlace {
    bool    exist = false;
    string  fileName;
    string  functionName;
    int32_t lineNumber;
};

class Logger : public Singleton<Logger>, public Object {
public:
    Logger();

    /**
     * Creates a Log entry
     * @warning At every Log object destruction the stream flushes. Might cause
     * performance issues
     */
    static LogEntry Log(ObjectTag tag = GENERAL, LogLevel level = INFO, const LogPlace& place = { });

    /**
     * Adds current time stamp to string stream
     * @note Format: HH.MM.SS.ms
     * @note CORE_LOG_DATE defined macro changes format to YY/MM/DD HH:MM:SS.ms
     */
    static std::stringstream& LogTimeStamp(std::stringstream& stream);

    static std::stringstream& LogTagText(std::stringstream& stream, ObjectTag tag);

    static std::stringstream& LogLevelText(std::stringstream& stream, LogLevel level);

    /**
     * Sets width and fill char for next value in stream
     * @param stream - stream to set values to
     * @param ch - char to fill the width with
     * @param width - width of filling
     * @return std::stringstream&
     */
    static std::stringstream& FillWidth(std::stringstream& stream, const char& ch, const int8_t& width);

    static string GetLogTypeText(ObjectTag tag);
    static string GetLogLevelText(LogLevel level);
    static string GetPlaceText(const LogPlace& place);
    static string GetPassText(PassInfo success);
    static string ToUpper(string str);

}; // class Logger

class LogEntry {
public:
    LogEntry(std::ostream& out, LogLevel level = INFO, ObjectTag tag = GENERAL, LogPlace place = { });
    ~LogEntry();

    template<class T>
    LogEntry& operator<<(const T& thing) {
        logStream << thing;
        return *this;
    };

private:
    LogLevel level;
    LogPlace logPlace;
    std::stringstream logStream;
    std::ostream& output;
}; // class Log

/**
 * Global wraper of Logger::Log for rapid development
 */
LogEntry Log(ObjectTag tag = GENERAL, LogLevel level = INFO, const LogPlace& place = { });


}

#endif //CORE_LOGGER_H
