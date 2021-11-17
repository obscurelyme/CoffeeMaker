#ifndef _coffeemaker_async_hpp
#define _coffeemaker_async_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <future>
#include <mutex>
#include <thread>

#include "Logger.hpp"
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

    class TimeoutTask {
      public:
      TimeoutTask(const std::string& name, std::function<void(void)> cb, int duration, bool throttle) :
          _callback(cb),
          _name(name),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _throttle(throttle),
          _thread(nullptr) {
        _timeoutMutex = new std::mutex();
      }
      TimeoutTask(const std::string& name, std::function<void(void)> cb, int duration) :
          _callback(cb),
          _name(name),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _throttle(true),
          _thread(nullptr) {
        _timeoutMutex = new std::mutex();
      }
      TimeoutTask(std::function<void(void)> cb, int duration) :
          _callback(cb),
          _name("UNKNOWN_TIMEOUT_TASK"),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _throttle(true),
          _thread(nullptr) {
        _timeoutMutex = new std::mutex();
      }

      ~TimeoutTask() {
        Cancel();
        if (_future.valid()) {
          _future.get();
        }
        if (_thread != nullptr && _thread->joinable()) {
          _thread->join();
          delete _thread;
          _thread = nullptr;
        }
      }

      void Start2() {
        if (!_running) {
          _running = true;
          _canceled = false;
          _thread = new std::thread([this] {
            _timer->Start();
            while (!_canceled) {
              std::this_thread::sleep_for(std::chrono::milliseconds(16));
              std::lock_guard<std::mutex> lk(*_timeoutMutex);
              if (_timer->Expired()) {
                _callback();
                _running = false;
                return;
              }
            }
            _running = false;
            return;
          });
        }
      }

      void Start() {
        if (!_running) {
          _running = true;
          _canceled = false;
          _future = std::async(std::launch::async, [this] {
            _timer->Start();
            // CM_LOGGER_INFO("{} Started on thread", _name);
            while (!_canceled) {
              std::this_thread::sleep_for(std::chrono::milliseconds(16));
              std::lock_guard<std::mutex> lk(*_timeoutMutex);
              if (_timer->Expired()) {
                // CM_LOGGER_INFO("{} Completed, {} Ticks compared to {} duration", _name, _timer->GetTicks(),
                //                _timer->GetInterval());
                _callback();
                _running = false;
                return;
              }
              // CM_LOGGER_INFO("{} Keep going", _name);
            }
            _running = false;
            // CM_LOGGER_INFO("{} Canceled thread", _name);
            return;
          });
        }
      }

      void Reset() {
        _canceled = false;
        _running = false;
      }

      void Cancel() {
        std::lock_guard<std::mutex> lk(*_timeoutMutex);
        _canceled = true;
      }

      void Pause() {
        std::lock_guard<std::mutex> lk(*_timeoutMutex);
        _timer->Pause();
        // CM_LOGGER_INFO("{} Paused at {}", _name, _timer->GetTicks());
      }

      void Unpause() {
        std::lock_guard<std::mutex> lk(*_timeoutMutex);
        _timer->Unpause();
        // CM_LOGGER_INFO("{} Resumed at {}", _name, _timer->GetTicks());
      }

      private:
      std::function<void(void)> _callback;
      std::string _name;
      bool _canceled{false};
      bool _running;
      std::future<void> _future;
      Scope<CoffeeMaker::StopWatch> _timer;
      std::mutex* _timeoutMutex;
      bool _throttle;
      std::thread* _thread;
    };

    class IntervalTask {
      public:
      IntervalTask(std::function<void(void)> cb, int duration) :
          _callback(cb),
          _canceled(false),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _mutex(new std::mutex()),
          _thread(nullptr) {}

      ~IntervalTask() {
        Cancel();
        if (_future.valid()) {
          _future.get();
        }
        if (_thread != nullptr && _thread->joinable()) {
          _thread->join();
        }
      }

      void Start2() {
        if (!_running) {
          _running = true;
          _canceled = false;
          _thread = new std::thread([this] {
            _timer->Start();
            while (!_canceled) {
              std::this_thread::sleep_for(std::chrono::milliseconds(16));
              std::lock_guard<std::mutex> lk(*_mutex);
              if (_timer->Expired()) {
                _callback();
                _running = false;
                _timer->Reset();
              }
            }
            _running = false;
            return;
          });
        }
      }

      /**
       * @brief This function is deprecated, use Start2 instead to leverage std::thread directly
       * @deprecated Do not use, leverage Start2() instead
       */
      void Start() {
        if (!_running) {
          _running = true;
          _future = std::async(std::launch::async | std::launch::deferred, [this] {
            _canceled = false;
            _timer->Start();
            while (!_canceled) {
              std::this_thread::sleep_for(std::chrono::milliseconds(16));
              std::lock_guard<std::mutex> lk(*_mutex);
              if (_timer->Expired()) {
                _callback();
                _timer->Reset();
              }
            }
            _running = false;
          });
        }
      }

      void Cancel() {
        std::lock_guard<std::mutex> lk(*_mutex);
        _canceled = true;
      }

      void Pause() {
        std::lock_guard<std::mutex> lk(*_mutex);
        _timer->Pause();
      }

      void Unpause() {
        std::lock_guard<std::mutex> lk(*_mutex);
        _timer->Unpause();
      }

      private:
      std::function<void(void)> _callback;
      bool _canceled;
      bool _running;
      std::future<void> _future;
      Scope<CoffeeMaker::StopWatch> _timer;
      std::mutex* _mutex;
      std::thread* _thread;
    };
  }  // namespace Async
}  // namespace CoffeeMaker

#endif
