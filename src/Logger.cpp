#include "Logger.hpp"

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
  _fileSink->set_level(spdlog::level::debug);

  _consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  _consoleSink->set_level(spdlog::level::trace);

  _errSink = std::make_shared<spdlog::sinks::stderr_color_sink_mt>();
  _errSink->set_level(spdlog::level::critical);

  _spdlog = new spdlog::logger("etc", {_fileSink, _consoleSink, _errSink});
}

Logger::~Logger() { delete _spdlog; }

void Logger::Trace(std::string msg) { _logger->_spdlog->trace(msg); }

void Logger::Debug(std::string msg) { _logger->_spdlog->debug(msg); }
void Logger::Warn(std::string msg) { _logger->_spdlog->warn(msg); }
void Logger::Info(std::string msg) { _logger->_spdlog->info(msg); }
void Logger::Error(std::string msg) { _logger->_spdlog->error(msg); }
void Logger::Critical(std::string msg) { _logger->_spdlog->critical(msg); }

spdlog::logger *Logger::Instance() {
  if (_logger == nullptr) {
    return nullptr;
  }
  return _logger->_spdlog;
}
