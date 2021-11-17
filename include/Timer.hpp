#ifndef _coffeemaker_timer_hpp
#define _coffeemaker_timer_hpp

#include <SDL2/SDL.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "Logger.hpp"

namespace CoffeeMaker {

  class Performance {
    public:
    explicit Performance(const std::string& name) : _start(std::chrono::high_resolution_clock::now()), _name(name) {}
    ~Performance() {
      using namespace std::chrono;

      auto end = high_resolution_clock::now();
      auto startTime = time_point_cast<microseconds>(_start).time_since_epoch();
      auto endTime = time_point_cast<microseconds>(end).time_since_epoch();

      auto us = endTime.count() - startTime.count();
      CM_LOGGER_INFO("Performance Timer [{}]: {} us, {} ms", _name, us, us * 0.001f);
    }

    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    std::string _name;
  };

  class Timer {
    public:
    Timer();

    void Start();
    Uint32 GetTicks();
    void Pause();
    void Unpause();
    void Stop();

    bool IsStarted();
    bool IsPaused();

    /**
     * Returns a parsed string of the timer's current time.
     * MM:SS
     */
    std::string toString();

    private:
    Uint32 _startTicks;
    Uint32 _pausedTicks;

    bool _paused;
    bool _started;
  };

  class StopWatch {
    public:
    explicit StopWatch(int interval) : _interval(interval) {}

    bool Expired() { return _timer.GetTicks() >= _interval; }

    Uint32 GetTicks() { return _timer.GetTicks(); }

    void Start() { _timer.Start(); }

    void Reset() {
      if (_timer.IsPaused()) {
        _timer.Stop();
        _timer.Start();
        _timer.Pause();
      } else {
        _timer.Stop();
        _timer.Start();
      }
    }

    void Pause() { _timer.Pause(); }

    void Unpause() { _timer.Unpause(); }

    void Stop() { _timer.Stop(); }

    Uint32 GetInterval() { return _interval; }

    private:
    CoffeeMaker::Timer _timer;
    Uint32 _interval{0};
  };

  class SDLTimer {
    public:
    SDLTimer(Uint32 delay, SDL_TimerCallback callback, void* params) :
        paused(SDL_CreateMutex()), _id(-1), _delay(delay), _callback(callback) {
      _pair.first = this;
      _pair.second = params;
    }
    ~SDLTimer() { Stop(); }

    void Start() { _id = SDL_AddTimer(_delay, _callback, &_pair); }
    void Stop() { SDL_RemoveTimer(_id); }
    void Cancel() { SDL_RemoveTimer(_id); }
    void Pause() { SDL_LockMutex(paused); }
    void Unpause() { SDL_UnlockMutex(paused); }

    SDL_mutex* paused;

    private:
    SDL_TimerID _id;
    Uint32 _delay;
    SDL_TimerCallback _callback;
    std::pair<SDLTimer*, void*> _pair;
  };

  class Timeout : public CoffeeMaker::Timer {
    public:
    explicit Timeout(Uint32 delay, std::function<void(void)> fn) : _delay(delay), _callback(fn), _started(false) {
      _timeouts.emplace_back(this);
    };
    ~Timeout() {
      for (auto it = _timeouts.begin(); it != _timeouts.end();) {
        if (this == *it) {
          it = _timeouts.erase(it);
          break;
        } else {
          ++it;
        }
      }
    };

    void Start() {
      if (!_started) {
        _started = true;
        CoffeeMaker::Timer::Start();
      }
    };

    bool Check() { return _started && GetTicks() >= _delay; };

    void Act() {
      CoffeeMaker::Timer::Stop();
      _started = false;
      std::invoke(_callback);
    };

    static void ProcessTimeouts() {
      for (auto& timeout : _timeouts) {
        if (timeout->Check()) {
          timeout->Act();
        }
      }
    }

    static void PauseAllTimeouts() {
      for (auto& to : _timeouts) {
        to->Pause();
      }
    }

    static void UnpauseAllTimeouts() {
      for (auto& to : _timeouts) {
        to->Unpause();
      }
    }

    private:
    Uint32 _delay;
    std::function<void(void)> _callback;
    bool _started;

    static std::vector<Timeout*> _timeouts;
  };

}  // namespace CoffeeMaker

#endif
