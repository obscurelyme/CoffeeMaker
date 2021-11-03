#include "Timer.hpp"

using namespace CoffeeMaker;

Timer::Timer() : _startTicks(0), _pausedTicks(0), _paused(false), _started(false) {}

void Timer::Start() {
  _started = true;
  _paused = false;

  _startTicks = SDL_GetTicks();
  _pausedTicks = 0;
}

void Timer::Stop() {
  _startTicks = 0;
  _pausedTicks = 0;
  _paused = false;
  _started = false;
}

void Timer::Pause() {
  if (_started && !_paused) {
    _paused = true;
    _pausedTicks = SDL_GetTicks() - _startTicks;
    _startTicks = 0;
  }
}

void Timer::Unpause() {
  if (_started && _paused) {
    _paused = false;

    _startTicks = SDL_GetTicks() - _pausedTicks;
    _pausedTicks = 0;
  }
}

Uint32 Timer::GetTicks() {
  Uint32 time = 0;

  if (_started) {
    if (_paused) {
      time = _pausedTicks;
    } else {
      time = SDL_GetTicks() - _startTicks;
    }
  }

  return time;
}

bool Timer::IsPaused() { return _paused; }

bool Timer::IsStarted() { return _started; }

std::string Timer::toString() {
  float totalSeconds = GetTicks() / 1000.0f;
  float totalMinutes = totalSeconds / 60;
  int integerMinutes = (int)totalMinutes;
  float remainingSeconds = totalMinutes - integerMinutes;
  int integerSeconds = (int)(remainingSeconds * 60);

  std::string secondTime =
      (integerSeconds >= 10 ? std::to_string(integerSeconds) : "0" + std::to_string(integerSeconds));
  return std::string(std::to_string(integerMinutes) + ":" + secondTime);
}

std::vector<Timeout*> CoffeeMaker::Timeout::_timeouts{};
