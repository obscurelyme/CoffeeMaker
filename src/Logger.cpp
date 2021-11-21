#include "Logger.hpp"

#include <functional>

using namespace CoffeeMaker;

Logger *Logger::_logger = nullptr;

void Logger::Init() {
  if (_logger == nullptr) {
    _logger = new Logger();
  }
}

void Logger::Destroy() {
  if (_logger != nullptr) {
    delete _logger;
  }
}

Logger::Logger() {
  _fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/debug.txt", true);
  _fileSink->set_level(spdlog::level::trace);

  _consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  _consoleSink->set_level(spdlog::level::debug);

  _errSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
  _errSink->set_level(spdlog::level::critical);

  _spdlog = new spdlog::logger("Gameplay Log", {_consoleSink, _errSink, _fileSink});

  _spdlog->set_level(spdlog::level::trace);
}

Logger::~Logger() { delete _spdlog; }

void Logger::Warn(fmt::v8::format_string<> fmt) { _logger->_spdlog->warn(fmt); }

void Logger::Info(fmt::v8::format_string<> fmt) { _logger->_spdlog->info(fmt); }

void Logger::Error(fmt::v8::format_string<> fmt) { _logger->_spdlog->error(fmt); }

void Logger::Critical(fmt::v8::format_string<> fmt) { _logger->_spdlog->critical(fmt); }

spdlog::logger *Logger::Instance() {
  if (_logger == nullptr) {
    return nullptr;
  }
  return _logger->_spdlog;
}
