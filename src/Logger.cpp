#include <core/Logger.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <utility>

namespace core {

Logger::Logger() : Object("Logger") {

}
Log Logger::Log(LOG_LEVEL level, LOG_TYPE type) {
    switch (level) {
        case   ERR: return core::Log(std::cout, ERR, type);
        case  WARN: return core::Log(std::cout, WARN, type);
        case  INFO: return core::Log(std::cout, INFO, type);
        case DEBUG: return core::Log(std::cout, DEBUG, type);
    }
    return core::Log(std::cout, ERR, INTERNAL);
}
string Logger::GetPassText(PASS_INFO success) {
   string afterText;

    switch (success) {
        case NO_INFO: afterText = ""; break;
        case    FAIL: afterText = "- failed"; break;
        case SUCCESS: afterText = "- success"; break;
    }

    return afterText;
}
string Logger::GetLogLevelText(LOG_LEVEL level) {
    string afterText;

    switch (level) {
        case   ERR: afterText = "ERROR! "; break;
        case  WARN: afterText = "WARN: "; break;
        case  INFO: afterText = ""; break;
        case DEBUG: afterText = ""; break;
    }

    return afterText;
}
string Logger::GetLogTypeText(LOG_TYPE log_type) {
    string preText;

    switch (log_type) {
        case  GENERAL: preText = "        "; break;
        case  NETWORK: preText = "|NET|   "; break;
        case INTERNAL: preText = "|CORE|  "; break;
        case  PHYSICS: preText = "|PHYS|  "; break;
        case   RENDER: preText = "|RENDER|"; break;
        case   WINDOW: preText = "|WINDOW|"; break;
    }

    return preText;
}
std::stringstream& Logger::AddTimeStamp(std::stringstream& stream) {
    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto fraction = now - seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

    const std::time_t cnow = std::chrono::system_clock::to_time_t(now);
    const std::tm localTime = *std::localtime(std::addressof(cnow) );

    // Macro is defined by CORE_LOG_DATE option in CMake
    #ifdef CORE_LOG_DATE
        stream << localTime.tm_year + 1900 << "/" << localTime.tm_mon + 1 << "/" << localTime.tm_mday << " ";
    #endif

    FillWidth(stream, '0', 2);
    stream << localTime.tm_hour << ":";

    FillWidth(stream, '0', 2);
    stream << localTime.tm_min << ":";

    FillWidth(stream, '0', 2);
    stream << localTime.tm_sec << ".";

    FillWidth(stream, '0', 3);
    stream << milliseconds.count();

    return stream;
}
std::stringstream &Logger::FillWidth(std::stringstream &stream, const char& ch, const int8_t& width) {
    stream.fill(ch);
    stream.width(width);

    return stream;
}
string Logger::ToUpper(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return std::move(str);
}
Log::~Log() {
    logStream << "\n";
    output << logStream.rdbuf();
    output.flush();
}
Log::Log(std::ostream &out, LOG_LEVEL level, LOG_TYPE type) : output(out) {
    logStream << "- ";
    Logger::AddTimeStamp(logStream) << " ";
    logStream << Logger::GetLogTypeText(type) << " ";
    logStream << Logger::GetLogLevelText(level);
}
} // namespace core