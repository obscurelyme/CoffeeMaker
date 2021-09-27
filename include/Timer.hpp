#ifndef _coffeemaker_timer_hpp
#define _coffeemaker_timer_hpp

#include <SDL2/SDL.h>

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

 private:
  Uint32 _startTicks;
  Uint32 _pausedTicks;

  bool _paused;
  bool _started;
};

}  // namespace CoffeeMaker

#endif
