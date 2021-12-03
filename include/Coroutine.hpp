#ifndef _coffeemaker_coroutine_hpp
#define _coffeemaker_coroutine_hpp

#ifdef COROUTINE_SUPPORT
#include <chrono>
#include <coroutine>
#include <iostream>
#include <thread>

namespace CoffeeMaker {

  using Suspend = std::suspend_always;
  using Never = std::suspend_never;

  class Coroutine {
    public:
    class promise_type {
      public:
      promise_type() { std::cout << "promise_type created" << std::endl; }
      ~promise_type() { std::cout << "promise_type destroyed" << std::endl; }

      Coroutine get_return_object() { return Coroutine{std::coroutine_handle<promise_type>::from_promise(*this)}; }
      void yield_value() { Suspend{}; }
      Never initial_suspend() { return {}; }
      Never final_suspend() noexcept { return {}; }
      void unhandled_exception() {}
      void return_void() {}
    };

    explicit Coroutine(std::coroutine_handle<promise_type> handle) : _handle(handle){};
    Coroutine() = default;
    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;
    Coroutine(Coroutine&& t) noexcept : _handle(t._handle) { t._handle = {}; }
    Coroutine& operator=(Coroutine&& t) noexcept {
      if (this == &t) return *this;
      if (_handle) _handle.destroy();
      _handle = t._handle;
      t._handle = {};
      return *this;
    }

    ~Coroutine() {
      // if (_handle) {
      //   _handle.destroy();
      // }
    }

    void Resume() {
      if (!_handle.done()) {
        _handle.resume();
      }
    }

    private:
    std::coroutine_handle<promise_type> _handle;
  };

  class Awaiter {
    public:
    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) {
      std::thread([handle] {
        // do expensive task...
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "await resuming" << std::endl;
        handle.resume();
      }).detach();
    }
    int await_resume() {
      std::cout << "resumed" << std::endl;
      return 4;
    }
  };

  class TimeoutAwaiter {
    public:
    explicit TimeoutAwaiter(int duration) {
      _clockStart = std::chrono::steady_clock::now();
      _duration = duration;
    }
    ~TimeoutAwaiter() = default;

    bool await_ready() { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) {
      std::thread([handle, this] {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _clockStart)
                   .count() < _duration) {
          std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        handle.resume();
      }).detach();
    }
    void await_resume() {}

    private:
    std::chrono::steady_clock::time_point _clockStart;
    int _duration;
    // int _clockPaused;
    // bool _started;
    // bool _paused;
  };

  class HttpAwaiter;
  class FileAwaiter;
}  // namespace CoffeeMaker

#endif

#ifdef COROUTINE_EXPERIMENTAL_SUPPORT
#include <experimental/coroutine>

namespace CoffeeMaker {

  using Suspend = std::experimental::suspend_always;
  using Never = std::experimental::suspend_never;

  class Coroutine {
    public:
    class promise_type {
      public:
      promise_type() { std::cout << "promise_type created" << std::endl; }
      ~promise_type() { std::cout << "promise_type destroyed" << std::endl; }

      Coroutine get_return_object() {
        return Coroutine{std::experimental::coroutine_handle<promise_type>::from_promise(*this)};
      }
      void yield_value() { Suspend{}; }
      Never initial_suspend() { return {}; }
      Never final_suspend() noexcept { return {}; }
      void unhandled_exception() {}
      void return_void() {}
    };

    explicit Coroutine(std::experimental::coroutine_handle<promise_type> handle) : _handle(handle){};
    Coroutine() = default;
    Coroutine(const Coroutine&) = delete;
    Coroutine& operator=(const Coroutine&) = delete;
    Coroutine(Coroutine&& t) noexcept : _handle(t._handle) { t._handle = {}; }
    Coroutine& operator=(Coroutine&& t) noexcept {
      if (this == &t) return *this;
      if (_handle) _handle.destroy();
      _handle = t._handle;
      t._handle = {};
      return *this;
    }

    ~Coroutine() {
      // if (_handle) {
      //   _handle.destroy();
      // }
    }

    void Resume() {
      if (!_handle.done()) {
        _handle.resume();
      }
    }

    private:
    std::experimental::coroutine_handle<promise_type> _handle;
  };

  class Awaiter {
    public:
    bool await_ready() { return false; }
    void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) {
      std::thread([handle] {
        // do expensive task...
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "await resuming" << std::endl;
        handle.resume();
      }).detach();
    }
    int await_resume() {
      std::cout << "resumed" << std::endl;
      return 4;
    }
  };

  class TimeoutAwaiter {
    public:
    explicit TimeoutAwaiter(int duration) {
      _clockStart = std::chrono::steady_clock::now();
      _duration = duration;
    }
    ~TimeoutAwaiter() = default;

    bool await_ready() { return false; }
    void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) {
      std::thread([handle, this] {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _clockStart)
                   .count() < _duration) {
          std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        handle.resume();
      }).detach();
    }
    void await_resume() {}

    private:
    std::chrono::steady_clock::time_point _clockStart;
    int _duration;
    // int _clockPaused;
    // bool _started;
    // bool _paused;
  };

  class HttpAwaiter;
  class FileAwaiter;
}  // namespace CoffeeMaker

#endif

#endif
