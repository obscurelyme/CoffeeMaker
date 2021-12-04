#include "DateTime.hpp"

std::string CoffeeMaker::DateTime::Format(const std::string& fmt, std::time_t time) {
  return fmt::format(fmt, fmt::localtime(time));
}

std::string CoffeeMaker::DateTime::Format(const std::string& fmt, std::tm time) { return fmt::format(fmt, time); }
