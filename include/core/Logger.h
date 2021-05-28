#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

#include <ostream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <utility>

#ifndef LOG_HERE
#   ifdef CORE_LOG_FULL_PATH
#       define LOG_HERE LogPlace(true, __FILE__, __FUNCTION__, __LINE__)
#   else
#       define LOG_HERE LogPlace(true, __FILENAME__, __FUNCTION__, __LINE__)
#   endif
#endif

#ifndef WARN_HERE
#   define WARN_HERE logLevel::WARN, LOG_HERE
#endif

#ifndef ERR_HERE
#   define ERR_HERE logLevel::ERR, LOG_HERE
#endif

#ifndef INFO_HERE
#   define INFO_HERE logLevel::INFO, LOG_HERE
#endif

#ifndef DEBUG_HERE
#   define DEBUG_HERE logLevel::DEBUG, LOG_HERE
#endif

#ifndef NEW_LINE
#   define NEW_LINE string('\n') + string(16, ' ') + string(' |')
#endif

namespace core {

enum logLevel {
    DEBUG,
    INFO,
    WARN,
    ERR,
};
enum objectTag {
    INTERNAL, // For engine logs
    GENERAL,  // For other logs
    NETWORK,  // Network module logs
    PHYSICS,  // Physics module logs
    MEMORY,   // For memory logs (allocs etc.)
    OBJECT,   // Objects logs
    WINDOW,   // Window module logs
    RENDER,   // Rendering module logs
    IMPORT,   // Importing logs
    SCENE,    // Scene module logs
    INPUT,    // Scene module logs
};
enum passInfo {
    SUCCESS,
    NO_INFO,
    FAIL,
};

struct LogPlace {
    LogPlace() { };
    LogPlace(bool exist, string file, string func, int32_t line)
        : exist(exist), fileName(std::move(file)), functionName(std::move(func)), lineNumber(line) { };

    bool        exist = false;
    std::string fileName;
    std::string functionName;
    int32_t     lineNumber;
};

class Logger : public Singleton<Logger>, public Object {
public:
    Logger();

    /**
     * Creates a Log entry
     * @warning At every Log object destruction the stream flushes. Might cause
     * performance issues
     */
    static Log Log(objectTag tag = GENERAL,
                   logLevel level = INFO,
                   const LogPlace& place = LogPlace());

    /**
     * Adds current time stamp to string stream
     * @note Format: HH.MM.SS.ms
     * @note CORE_LOG_DATE defined macro changes format to YY/MM/DD HH:MM:SS.ms
     */
    static std::stringstream& LogTimeStamp(std::stringstream& stream);

    static std::stringstream& LogTagText(std::stringstream& stream, objectTag tag);

    static std::stringstream& LogLevelText(std::stringstream& stream, logLevel level);

    /**
     * Sets width and fill char for next value in stream
     * @param stream - stream to set values to
     * @param ch - char to fill the width with
     * @param width - width of filling
     * @return std::stringstream&
     */
    static std::stringstream& FillWidth(std::stringstream& stream, const char& ch, const int8_t& width);

    static string GetLogTypeText(objectTag tag);
    static string GetLogLevelText(logLevel level);
    static string GetPlaceText(const LogPlace& place);
    static string GetPassText(passInfo success);
    static string ToUpper(string str);

}; // class Logger

class Log {
public:
    Log(std::ostream& out,
        logLevel level = INFO,
        objectTag tag  = GENERAL,
        LogPlace place = LogPlace());
    ~Log();

    template<class T>
    Log& operator<<(const T& thing) {
        logStream << thing;
        return *this;
    };

private:
    logLevel level;
    LogPlace logPlace;
    std::stringstream logStream;
    std::ostream& output;
}; // class Log

}

#endif //CORE_LOGGER_H
