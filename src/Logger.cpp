#include <core/Logger.h>
#include <iostream>
#include <ctime>
#include <utility>

namespace core {

Logger::Logger() : Object("Logger") {

}
Log Logger::Log(objectTag tag, logLevel level, const LogPlace& place) {
    switch (level) {
        case   ERR: return core::Log(std::cout, ERR,   tag, place);
        case  WARN: return core::Log(std::cout, WARN,  tag, place);
        case  INFO: return core::Log(std::cout, INFO,  tag, place);
        case DEBUG: return core::Log(std::cout, DEBUG, tag, place);
    }
    return core::Log(std::cout, ERR, INTERNAL);
}
string Logger::GetPassText(passInfo success) {
   string text;

    switch (success) {
        case NO_INFO: text = ""; break;
        case    FAIL: text = "- failed"; break;
        case SUCCESS: text = "- success"; break;
    }

    return text;
}
string Logger::GetLogLevelText(logLevel level) {
    string text;

    switch (level) {
        case   ERR: text = " ERROR! "; break;
        case  WARN: text = " WARN: "; break;
        case  INFO: text = " ";        break;
        case DEBUG: text = " ";        break;
    }

    return text;
}
string Logger::GetLogTypeText(objectTag tag) {
    string text;

    switch (tag) {
        case  GENERAL: text = "        "; break;
        case   OBJECT: text = "       >"; break;
        case  NETWORK: text = "   |NET|"; break;
        case   MEMORY: text = "   |MEM|"; break;
        case INTERNAL: text = "  |CORE|"; break;
        case  PHYSICS: text = "  |PHYS|"; break;
        case    INPUT: text = " |INPUT|"; break;
        case    SCENE: text = " |SCENE|"; break;
        case   IMPORT: text = "|IMPORT|"; break;
        case   RENDER: text = "|RENDER|"; break;
        case   WINDOW: text = "|WINDOW|"; break;
    }

    return text;
}
string Logger::GetPlaceText(const LogPlace& place) {
    // TODO: Add build option to include place.functionName in the text

    if ( !place.exist ) {
        return "";
    }

    string text = " - at [";

    text += place.fileName;
    text += ":";
    text += std::to_string(place.lineNumber);
    text += "]";

    return text;
}
std::stringstream& Logger::LogTimeStamp(std::stringstream& stream) {
    // FIXME: THIS IS SO HEAVY! For every log?! Refactoring needed!

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

    // FIXME: Ugly, Refactoring needed!
    FillWidth(stream, '0', 2);
    stream << localTime.tm_hour << ":";

    FillWidth(stream, '0', 2);
    stream << localTime.tm_min << ":";

    FillWidth(stream, '0', 2);
    stream << localTime.tm_sec << ".";

    FillWidth(stream, '0', 3);
    stream << milliseconds.count();

    stream << " ";

    return stream;
}
std::stringstream &Logger::LogTagText(std::stringstream &stream, objectTag tag) {
    stream << GetLogTypeText(tag);

    return stream;
}
std::stringstream &Logger::LogLevelText(std::stringstream &stream, logLevel level) {
    stream << GetLogLevelText(level);

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
    logStream << Logger::GetPlaceText(logPlace);
    logStream << "\n";
    output << logStream.rdbuf();
    output.flush();
}
Log::Log(std::ostream &out, logLevel level, objectTag tag, LogPlace logPlace) :
output(out),
level(level),
logPlace(std::move(logPlace))
{
    logStream << "- ";
    Logger::LogTimeStamp(logStream);
    Logger::LogTagText(logStream, tag);
    Logger::LogLevelText(logStream, level);
}

} // namespace core