#ifndef _coffeemaker_async_hpp
#define _coffeemaker_async_hpp

#include <functional>
#include <future>

#include "Timer.hpp"
#include "Utilities.hpp"

namespace CoffeeMaker {
  /**
   * @brief Basic Async task running library
   */
  namespace Async {
    template <typename T>
    using Future = std::future<T>;

    template <typename T, typename... Args>
    using Function = std::function<T(Args... args)>;

    /**
     * @brief Runs a given Function on another thread
     *
     * @tparam T Return value type of the Function
     * @tparam F Function type
     * @tparam Args Optional arguments to be passed to the Function
     * @param fn Function to execute
     * @param args Arguments to forward to Function
     * @return Future<T>
     */
    template <typename T, typename F, typename... Args>
    Future<T> Run(F fn, Args&&... args) {
      return std::async(std::launch::async, fn, std::forward<Args&&>(args)...);
    }

    template <typename T>
    class TimeoutTask {
      public:
      TimeoutTask(std::function<T(void)> cb, int duration) :
          _callback(cb), _canceled(false), _running(false), _timer(CreateScope<CoffeeMaker::StopWatch>(duration)) {}

      ~TimeoutTask() { Cancel(); }

      void Start() {
        if (!_running) {
          _running = true;
          _future = std::async(std::launch::async, [this] {
            _canceled = false;
            _timer->Start();
            while (!_canceled) {
              if (_timer->Expired()) {
                _running = false;
                return _callback();
              }
            }
          });
        }
      }

      void Cancel() { _canceled = true; }

      void Pause() { _timer->Pause(); }

      void Unpause() { _timer->Unpause(); }

      T Get() { return _future.get(); }

      private:
      std::function<T(void)> _callback;
      bool _canceled;
      bool _running;
      std::future<T> _future;
      Scope<CoffeeMaker::StopWatch> _timer;
    };

    class IntervalTask {
      public:
      IntervalTask(std::function<void(void)> cb, int duration) :
          _callback(cb), _canceled(false), _running(false), _timer(CreateScope<CoffeeMaker::StopWatch>(duration)) {}

      ~IntervalTask() { Cancel(); }

      void Start() {
        if (!_running) {
          _running = true;
          _future = std::async(std::launch::async, [this] {
            _canceled = false;
            _timer->Start();
            while (!_canceled) {
              if (_timer->Expired()) {
                _callback();
                _timer->Reset();
              }
            }
          });
        }
      }

      void Cancel() {
        _canceled = true;
        _running = false;
      }

      void Pause() { _timer->Pause(); }

      void Unpause() { _timer->Unpause(); }

      private:
      std::function<void(void)> _callback;
      bool _canceled;
      bool _running;
      std::future<void> _future;
      Scope<CoffeeMaker::StopWatch> _timer;
    };
  };  // namespace Async
}  // namespace CoffeeMaker

#endif
