#ifndef _coffeemaker_logger_hpp
#define _coffeemaker_logger_hpp

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace CoffeeMaker {
class Logger {
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

}  // namespace CoffeeMaker

// Logging macros
#define CM_LOGGER_INIT() CoffeeMaker::Logger::Init()
#define CM_LOGGER_DESTROY() CoffeeMaker::Logger::Destroy()
#define CM_LOGGER_CRITICAL(...) \
  CoffeeMaker::Logger::Instance()->critical(__VA_ARGS__)
#define CM_LOGGER_ERROR(...) CoffeeMaker::Logger::Instance()->error(__VA_ARGS__)
#define CM_LOGGER_WARN(...) CoffeeMaker::Logger::Instance()->warn(__VA_ARGS__)
#define CM_LOGGER_INFO(...) CoffeeMaker::Logger::Instance()->info(__VA_ARGS__)
#define CM_LOGGER_TRACE(...) CoffeeMaker::Logger::Instance()->trace(__VA_ARGS__)

#endif
