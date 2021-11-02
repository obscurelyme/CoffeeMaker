#ifndef _coffeemaker_timer_hpp
#define _coffeemaker_timer_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <string>

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
    explicit Timeout(Uint32 delay, std::function<void(void)> fn) : _delay(delay), _callback(fn), _started(false){};
    ~Timeout() = default;

    void Start() {
      if (!_started) {
        _started = true;
        CoffeeMaker::Timer::Start();
      }
    };

    bool Check() { return GetTicks() >= _delay; };

    void Act() {
      if (Check()) {
        std::invoke(_callback);
        CoffeeMaker::Timer::Stop();
        _started = false;
      }
    };

    private:
    Uint32 _delay;
    std::function<void(void)> _callback;
    bool _started;
  };

}  // namespace CoffeeMaker

#endif
