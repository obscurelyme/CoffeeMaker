#include "DateTime.hpp"

std::chrono::system_clock::time_point CoffeeMaker::DateTime::Now() { return std::chrono::system_clock::now(); }

std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> NowMs() {
  return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
}

std::string CoffeeMaker::DateTime::Format(const std::string& fmt, std::time_t time) {
  return fmt::format(fmt, fmt::localtime(time));
}

std::string CoffeeMaker::DateTime::Format(const std::string& fmt, std::tm time) { return fmt::format(fmt, time); }
