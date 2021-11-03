#ifndef _coffeemaker_timer_hpp
#define _coffeemaker_timer_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <string>
#include <vector>

namespace CoffeeMaker {

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
