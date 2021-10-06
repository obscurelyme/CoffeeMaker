#include "Timer.hpp"

using namespace CoffeeMaker;

Timer::Timer()
    : _startTicks(0), _pausedTicks(0), _paused(false), _started(false) {}

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
