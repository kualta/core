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
  /// Since Logger is a singleton, it must not be cloneable and assignable
  Logger(Logger& other) = delete;
  void operator=(const Logger &) = delete;


  static Logger* GetInstance();


  void Log(LOG_LEVEL level, const std::string& message);
  void Log(LOG_LEVEL level, const std::string& message, PASS_INFO success);


private:
    void LogInfo(const std::string& message, PASS_INFO success);
    void LogWarn(const std::string& message, PASS_INFO success);
    void LogError(const std::string& message, PASS_INFO success);
    std::string AfterText(PASS_INFO success);

    std::string successText = "- success";
    std::string failText = "- failed";

    static Logger instance;

};



}

#endif //INTERFACERS_LOGGER_H
