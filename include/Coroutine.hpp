#ifndef _coffeemaker_coroutine_hpp
#define _coffeemaker_coroutine_hpp

#include <SDL2/SDL.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#ifdef COROUTINE_SUPPORT
#include <coroutine>

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

    ~Coroutine() = default;

    void Resume() {
      if (!_handle.done()) {
        _handle.resume();
      }
    }

    private:
    std::coroutine_handle<promise_type> _handle;
  };

  template <typename ReturnType>
  class IAwaiter {
    virtual bool await_ready() = 0;
    virtual void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) = 0;
    virtual ReturnType await_resume() = 0;
  };

  class Awaiter : public IAwaiter<int> {
    public:
    bool await_ready() override { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) override {
      std::thread([handle] {
        // do expensive task...
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "await resuming" << std::endl;
        handle.resume();
      }).detach();
    }
    int await_resume() override {
      std::cout << "resumed" << std::endl;
      return 4;
    }
  };

  class TimeoutAwaiter : public IAwaiter<void> {
    public:
    explicit TimeoutAwaiter(int duration) : _clockStart(std::chrono::steady_clock::now()), _duration(duration) {}
    ~TimeoutAwaiter() = default;

    bool await_ready() override { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) override {
      std::thread([handle, this] {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _clockStart)
                   .count() < _duration) {
          std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        handle.resume();
      }).detach();
    }
    void await_resume() override {}

    private:
    std::chrono::steady_clock::time_point _clockStart;
    int _duration;
  };

  class HttpAwaiter;

  class ReadFileAwaiter : public IAwaiter<std::string> {
    public:
    explicit ReadFileAwaiter(const std::string& fileName) : _fileName(fileName), _result(nullptr), _str("") {}
    ~ReadFileAwaiter() {}

    bool await_ready() override { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) override {
      std::thread([handle, this] {
        SDL_RWops* file = SDL_RWFromFile(_fileName.c_str(), "r");
        if (file == NULL) {
          _str = std::string{"Could not read file!"};
          handle.resume();
          return;
        }
        Sint64 resultSize = SDL_RWsize(file);
        _result = (char*)malloc(resultSize + 1);
        char* buf = _result;
        Sint64 nb_read_total = 0;
        Sint64 nb_read = 1;
        while (nb_read_total < resultSize && nb_read != 0) {
          nb_read = SDL_RWread(file, buf, 1, resultSize - nb_read_total);
          nb_read_total += nb_read;
          buf += nb_read;
        }
        SDL_RWclose(file);
        if (nb_read_total != resultSize) {
          free(_result);
        }
        _result[nb_read_total] = '\0';
        _str = std::string{_result};
        handle.resume();
      }).detach();
    }
    std::string await_resume() override { return _str; }

    private:
    std::string _fileName;
    char* _result;
    std::string _str;
  };

  class WriteFileAwaiter : public IAwaiter<bool> {
    public:
    explicit WriteFileAwaiter(const std::string& fileName, const std::string& data) :
        _fileName(fileName), _data(data), _result(false) {}
    ~WriteFileAwaiter() {}

    bool await_ready() override { return false; }
    void await_suspend(std::coroutine_handle<Coroutine::promise_type> handle) override {
      std::thread([handle, this] {
        SDL_RWops* file = SDL_RWFromFile(_fileName.c_str(), "w");
        if (file != NULL) {
          const char* str = _data.c_str();
          size_t len = SDL_strlen(str);
          if (SDL_RWwrite(file, str, 1, len) != len) {
            _result = false;
          } else {
            _result = true;
          }
          SDL_RWclose(file);
        }
        handle.resume();
      }).detach();
    }
    bool await_resume() override { return _result; }

    private:
    std::string _fileName;
    std::string _data;
    bool _result;
  };
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
      Suspend yield_value() { return {}; }
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

    ~Coroutine() = default;

    void Resume() {
      if (!_handle.done()) {
        _handle.resume();
      }
    }

    private:
    std::experimental::coroutine_handle<promise_type> _handle;
  };

  template <typename ReturnType>
  class IAwaiter {
    virtual bool await_ready() = 0;
    virtual void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) = 0;
    virtual ReturnType await_resume() = 0;
  };

  class Awaiter {
    public:
    bool await_ready() { return false; }
    void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) {
      std::thread([handle] {
        // do expensive task...
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "await resuming" << std::endl;
        static_cast<std::experimental::coroutine_handle<Coroutine::promise_type>>(handle).resume();
      }).detach();
    }
    int await_resume() {
      std::cout << "resumed" << std::endl;
      return 4;
    }
  };

  class TimeoutAwaiter {
    public:
    explicit TimeoutAwaiter(int duration) : _clockStart(std::chrono::steady_clock::now()), _duration(duration) {}
    ~TimeoutAwaiter() = default;

    bool await_ready() { return false; }
    void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) {
      std::thread([this, handle] {
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _clockStart)
                   .count() < _duration) {
          std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        static_cast<std::experimental::coroutine_handle<Coroutine::promise_type>>(handle).resume();
      }).detach();
    }
    void await_resume() {}

    private:
    std::chrono::steady_clock::time_point _clockStart;
    int _duration;
  };

  class ReadFileAwaiter : public IAwaiter<std::string> {
    public:
    explicit ReadFileAwaiter(const std::string& fileName) : _fileName(fileName), _result(nullptr), _str("") {}
    ~ReadFileAwaiter() {}

    bool await_ready() override { return false; }
    void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) override {
      std::thread([handle, this] {
        SDL_RWops* file = SDL_RWFromFile(_fileName.c_str(), "r");
        if (file == NULL) {
          _str = std::string{"Could not read file!"};
          handle.resume();
          return;
        }
        Sint64 resultSize = SDL_RWsize(file);
        _result = (char*)malloc(resultSize + 1);
        char* buf = _result;
        Sint64 nb_read_total = 0;
        Sint64 nb_read = 1;
        while (nb_read_total < resultSize && nb_read != 0) {
          nb_read = SDL_RWread(file, buf, 1, resultSize - nb_read_total);
          nb_read_total += nb_read;
          buf += nb_read;
        }
        SDL_RWclose(file);
        if (nb_read_total != resultSize) {
          free(_result);
        }
        _result[nb_read_total] = '\0';
        _str = std::string{_result};
        static_cast<std::experimental::coroutine_handle<Coroutine::promise_type>>(handle).resume();
      }).detach();
    }
    std::string await_resume() override { return _str; }

    private:
    std::string _fileName;
    char* _result;
    std::string _str;
  };

  class WriteFileAwaiter : public IAwaiter<bool> {
    public:
    explicit WriteFileAwaiter(const std::string& fileName, const std::string& data) :
        _fileName(fileName), _data(data), _result(false) {}
    ~WriteFileAwaiter() {}

    bool await_ready() override { return false; }
    void await_suspend(std::experimental::coroutine_handle<Coroutine::promise_type> handle) override {
      std::thread([handle, this] {
        SDL_RWops* file = SDL_RWFromFile(_fileName.c_str(), "w");
        if (file != NULL) {
          const char* str = _data.c_str();
          size_t len = SDL_strlen(str);
          if (SDL_RWwrite(file, str, 1, len) != len) {
            _result = false;
          } else {
            _result = true;
          }
          SDL_RWclose(file);
        }
        static_cast<std::experimental::coroutine_handle<Coroutine::promise_type>>(handle).resume();
      }).detach();
    }
    bool await_resume() override { return _result; }

    private:
    std::string _fileName;
    std::string _data;
    bool _result;
  };
}  // namespace CoffeeMaker

#endif

#endif
