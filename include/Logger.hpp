#ifndef _coffeemaker_logger_hpp
#define _coffeemaker_logger_hpp

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace CoffeeMaker
{
  class Logger
  {
  public:
    static void Init();
    static spdlog::logger *Instance();
    static void Trace(std::string msg);
    static void Debug(std::string msg);
    static void Warn(std::string msg);
    static void Info(std::string msg);
    static void Error(std::string msg);
    static void Critical(std::string msg);
    static void Destroy();

  private:
    Logger();
    ~Logger();
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> _fileSink;
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> _consoleSink;
    std::shared_ptr<spdlog::sinks::stderr_color_sink_mt> _errSink;
    spdlog::logger *_spdlog;
    static Logger *_logger;
  };

} // namespace CoffeeMaker

#endif