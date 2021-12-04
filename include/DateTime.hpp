#ifndef _coffeemaker_date_hpp
#define _coffeemaker_date_hpp

#include <fmt/chrono.h>

#include <chrono>

namespace CoffeeMaker {

  /**
   * @brief Utilities for DateTime objects
   *
   * @see https://en.cppreference.com/w/cpp/chrono/c/strftime
   */
  namespace DateTime {

    /**
     * @brief Returns a time_point indicating the current system time.
     *
     * @return std::chrono::system_clock::time_point
     */
    inline auto Now() { return std::chrono::system_clock::now(); }

    /**
     * @brief Returns a time_point, in milliseconds, indicating the current system time.
     *
     * @return std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds>
     */
    inline auto NowMs() {
      return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
    }

    /**
     * @brief Convert a given time point into millisecond precision.
     *
     * @param timePoint
     * @return auto
     */
    inline auto ToMilliseconds(std::chrono::system_clock::time_point timePoint) {
      return std::chrono::time_point_cast<std::chrono::milliseconds>(timePoint);
    }

    /**
     * @brief Convert a given time point into microsecond precision.
     *
     * @param timePoint
     * @return auto
     */
    inline auto ToMicroseconds(std::chrono::system_clock::time_point timePoint) {
      return std::chrono::time_point_cast<std::chrono::microseconds>(timePoint);
    }

    /**
     * @brief Formats a given std::chrono::time_point to a provided formatted string
     * @example
     *
     * @see https://en.cppreference.com/w/cpp/chrono/c/strftime for a list of valid characters to map
     * @param fmt
     * @param time
     * @return std::string
     */
    template <typename ClockType, typename Precision>
    std::string Format(const std::string& fmt, std::chrono::time_point<ClockType, Precision> time) {
      auto n = std::chrono::system_clock::to_time_t(time);
      return fmt::format(fmt, fmt::localtime(n));
    }

    /**
     * @brief Formats a given std::time_t to a provided formatted string
     * @example
     *
     * @see https://en.cppreference.com/w/cpp/chrono/c/strftime for a list of valid characters to map
     * @param fmt
     * @param time
     * @return std::string
     */
    std::string Format(const std::string& fmt, std::time_t time);

    /**
     * @brief Formats a given std::tm to a provided formatted string
     * @example
     *
     * @see https://en.cppreference.com/w/cpp/chrono/c/strftime for a list of valid characters to map
     * @param fmt
     * @param time
     * @return std::string
     */
    std::string Format(const std::string& fmt, std::tm time);

  }  // namespace DateTime

}  // namespace CoffeeMaker

#endif
