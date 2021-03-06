#ifndef _coffeemaker_logger_hpp
#define _coffeemaker_logger_hpp

#include <fmt/compile.h>
#include <fmt/core.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <iostream>

#ifdef COFFEEMAKER_LOGGER_SOURCE_LOCATION
#include <source_location>
#endif

namespace CoffeeMaker {
  class Logger {
    public:
    static void Init();
    static spdlog::logger *Instance();

    // template <typename S, typename... Args>
    // static void Trace(S, Args &&...) {
    //   // _logger->_spdlog->trace(fmt::format(std::forward<S>(fmt), std::forward<Args &&>(args)...));
    // }

    template <typename... Args>
    static void Trace(fmt::format_string<Args...>, Args &&...) {
      // _logger->_spdlog->trace(fmt, args...);
    }
#ifdef COFFEEMAKER_LOGGER_SOURCE_LOCATION
    template <typename S, typename... Args>
    static void Debug(S fmt, Args... args, const std::source_location &location = std::source_location::current()) {
      std::string sourceFmt = fmt::format(fmt::runtime("Source: [ file={}, line={}, function={} ]"),
                                          location.file_name(), location.line(), location.function_name());
      _logger->_spdlog->debug(
          fmt::format(fmt::runtime(std::forward<S>(fmt) + " - " + sourceFmt), std::forward<Args &&>(args)...));
    }
#else
    // template <typename S, typename... Args>
    // static void Debug(S, Args &&...) {
    //   //_logger->_spdlog->debug(fmt::format(std::forward<S>(fmt), std::forward<Args &&>(args)...));
    // }

    template <typename... Args>
    static void Debug(fmt::format_string<Args...>, Args &&...) {
      // _logger->_spdlog->debug(fmt, args...);
    }

    // template <typename S>
    // static void Debug(S fmt);
#endif
    static void Warn(fmt::v8::format_string<> fmt);
    static void Info(fmt::v8::format_string<> fmt);
    static void Error(fmt::v8::format_string<> fmt);
    static void Critical(fmt::v8::format_string<> fmt);
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
#define CM_LOGGER_CRITICAL(...) CoffeeMaker::Logger::Instance()->critical(__VA_ARGS__)
#define CM_LOGGER_ERROR(...) CoffeeMaker::Logger::Instance()->error(__VA_ARGS__)
#define CM_LOGGER_WARN(...) CoffeeMaker::Logger::Instance()->warn(__VA_ARGS__)
#define CM_LOGGER_INFO(...) CoffeeMaker::Logger::Instance()->info(__VA_ARGS__)
#define CM_LOGGER_DEBUG(...) CoffeeMaker::Logger::Instance()->debug(__VA_ARGS__)
#define CM_LOGGER_TRACE(...) CoffeeMaker::Logger::Instance()->trace(__VA_ARGS__)

#endif
