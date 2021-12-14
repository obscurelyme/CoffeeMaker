#ifndef _coffeemaker_async_hpp
#define _coffeemaker_async_hpp

#include <SDL2/SDL.h>

#include <atomic>
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
     * @brief Basic Async Task utility that wraps std::packaged_task
     *
     * @tparam T
     * @tparam Args
     */
    template <typename T, typename... Args>
    class Task;

    template <typename T, typename... Args>
    class Task<T(Args...)> {
      public:
      explicit Task(std::function<T(Args...)> fp) : _value(nullptr) {
        _packagedTask = new std::packaged_task<T(Args...)>(fp);
        _future = _packagedTask->get_future();
        _thread = new std::thread(std::move(*_packagedTask));
      }

      ~Task() {
        Wait();
        delete _packagedTask;
      }

      /**
       * @brief Blocks the calling thread until the task completes its work.
       *
       * @return Task*
       */
      Task* Wait() {
        if (_thread != nullptr && _thread->joinable()) {
          _thread->join();
          delete _thread;
          _thread = nullptr;
          _value = _future.get();
        }
        return this;
      }

      /**
       * @brief Return the value as a result of the task.
       *
       * @return T
       */
      T Get() { return _value; }

      private:
      std::packaged_task<T(Args...)>* _packagedTask;
      std::future<T> _future;
      std::thread* _thread;
      T _value;
    };

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
      TimeoutTask(const std::string& name, std::function<void(void)> cb, int duration) :
          _callback(cb),
          _name(name),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _thread(nullptr),
          _shouldKill(false) {
        _timeoutMutex = new std::mutex();
      }
      TimeoutTask(std::function<void(void)> cb, int duration) :
          _callback(cb),
          _name("UNKNOWN_TIMEOUT_TASK"),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _thread(nullptr),
          _shouldKill(false) {
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
        delete _timeoutMutex;
      }

      void Start() {
        if (!_running) {
          _running = true;
          _canceled = false;
          if (_shouldKill) {
            // CM_LOGGER_DEBUG("{} thread will be killed", _name);
            _thread->join();
            delete _thread;
            // CM_LOGGER_DEBUG("{} thread was killed", _name);
          } else {
            // CM_LOGGER_DEBUG("{} thread was NOT killed", _name);
          }
          // CM_LOGGER_DEBUG("{} thread was created", _name);
          _thread = new std::thread([this] {
            _shouldKill = false;
            _timer->Start();
            while (!_canceled) {
              std::this_thread::sleep_for(std::chrono::milliseconds(16));
              std::lock_guard<std::mutex> lk(*_timeoutMutex);
              if (_timer->Expired()) {
                _callback();
                _running = false;
                _shouldKill = true;
                return;
              }
            }
            _running = false;
            _shouldKill = true;
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
        CoffeeMaker::Logger::Trace("[TIMEOUT][{}] Canceled at {}", _name, _timer->GetTicks());
      }

      void Pause() {
        std::lock_guard<std::mutex> lk(*_timeoutMutex);
        _timer->Pause();
        CoffeeMaker::Logger::Trace("[TIMEOUT][{}] Paused at {}", _name, _timer->GetTicks());
      }

      void Unpause() {
        std::lock_guard<std::mutex> lk(*_timeoutMutex);
        _timer->Unpause();
        CoffeeMaker::Logger::Trace("[TIMEOUT][{}] Resumed at {}", _name, _timer->GetTicks());
      }

      private:
      std::function<void(void)> _callback;
      std::string _name;
      bool _canceled{false};
      bool _running;
      std::future<void> _future;
      Scope<CoffeeMaker::StopWatch> _timer;
      std::mutex* _timeoutMutex;
      std::thread* _thread;
      std::atomic<bool> _shouldKill;
    };

    class IntervalTask {
      public:
      IntervalTask(std::function<void(void)> cb, int duration) :
          _callback(cb),
          _canceled(false),
          _running(false),
          _timer(CreateScope<CoffeeMaker::StopWatch>(duration)),
          _mutex(new std::mutex()),
          _thread(nullptr),
          _shouldKill(false) {}

      ~IntervalTask() {
        Cancel();
        if (_future.valid()) {
          _future.get();
        }
        if (_thread != nullptr && _thread->joinable()) {
          _thread->join();
          delete _thread;
          _thread = nullptr;
        }
        delete _mutex;
      }

      void Start() {
        if (!_running) {
          _running = true;
          _canceled = false;
          if (_shouldKill) {
            CoffeeMaker::Logger::Trace("{} thread will be killed", "Interval");
            _thread->join();
            delete _thread;
            CoffeeMaker::Logger::Trace("{} thread was killed", "Interval");
          }
          CoffeeMaker::Logger::Trace("{} thread was created", "Interval");
          _thread = new std::thread([this] {
            _shouldKill = false;
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
            _shouldKill = true;
            return;
          });
        }
      }

      void Cancel() {
        std::lock_guard<std::mutex> lk(*_mutex);
        _canceled = true;
        CoffeeMaker::Logger::Trace("[INTERVAL][undefined] Resumed at {}", _timer->GetTicks());
      }

      void Pause() {
        std::lock_guard<std::mutex> lk(*_mutex);
        _timer->Pause();
        CoffeeMaker::Logger::Trace("[INTERVAL][undefined] Resumed at {}", _timer->GetTicks());
      }

      void Unpause() {
        std::lock_guard<std::mutex> lk(*_mutex);
        _timer->Unpause();
        CoffeeMaker::Logger::Trace("[INTERVAL][undefined] Resumed at {}", _timer->GetTicks());
      }

      private:
      std::function<void(void)> _callback;
      bool _canceled;
      bool _running;
      std::future<void> _future;
      Scope<CoffeeMaker::StopWatch> _timer;
      std::mutex* _mutex;
      std::thread* _thread;
      std::atomic<bool> _shouldKill;
    };
  }  // namespace Async
}  // namespace CoffeeMaker

#endif
