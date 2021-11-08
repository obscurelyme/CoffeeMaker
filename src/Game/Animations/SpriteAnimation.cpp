#include "Game/Animations/SpriteAnimation.hpp"

int Animations::SpriteAnimation::_uid = 0;
std::vector<Animations::SpriteAnimation*> Animations::SpriteAnimation::_animations = {};

void Animations::SpriteAnimation::ProcessSpriteAnimations() {
  for (auto animation : _animations) {
    animation->Update();
  }
}

Animations::SpriteAnimation::SpriteAnimation(Ref<CoffeeMaker::Sprite> sprite, int duration, int loops) :
    _sprite(sprite),
    _duration(duration),
    _loops(loops),
    _started(false),
    _durationPerFrame(0),
    _currentFrame(0),
    _id(0) {
  _animations.push_back(this);
}

Animations::SpriteAnimation::~SpriteAnimation() {
  for (auto animation = _animations.begin(); animation != _animations.end();) {
    if (_id == (*animation)->_id) {
      animation = _animations.erase(animation);
      break;
    } else {
      ++animation;
    }
  }
}

void Animations::SpriteAnimation::Update() {
  if (_started) {
    if (_stopwatch->Expired()) {
      if (_currentFrame == _frames.size() - 1) {
        if (_loops == -1) {
          _currentFrame = 0;
        } else if (_loops > 0) {
          _loops--;
          _currentFrame = 0;
        } else {
          _stopwatch->Stop();
          _started = false;
        }
      } else {
        _currentFrame++;
      }
      _stopwatch->Reset();
    }

    _sprite->clipRect = _frames[_currentFrame];
  }
}

void Animations::SpriteAnimation::AddFrame(SDL_Rect frame) {
  if (!_started) {
    _frames.push_back(frame);
    _durationPerFrame = static_cast<int>(_duration / _frames.size());
  }
}

void Animations::SpriteAnimation::Render() { _sprite->Render(); }

void Animations::SpriteAnimation::Stop() { _stopwatch->Stop(); }

void Animations::SpriteAnimation::Start() {
  if (!_started) {
    _stopwatch = CreateScope<CoffeeMaker::StopWatch>(_durationPerFrame);
    _stopwatch->Start();
    _started = true;
  }
}

void Animations::SpriteAnimation::Pause() { _stopwatch->Pause(); }

void Animations::SpriteAnimation::Unpause() { _stopwatch->Unpause(); }
