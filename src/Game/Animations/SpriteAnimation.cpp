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
  _id = ++_uid;
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
          _onCompleteCallback();
        }
      } else {
        _currentFrame++;
      }
      _stopwatch->Reset();
    }
  }
}

void Animations::SpriteAnimation::AddFrame(SDL_Rect frame) {
  if (!_started) {
    _frames.push_back(frame);
    _durationPerFrame = static_cast<int>(_duration / _frames.size());
  }
}

void Animations::SpriteAnimation::Render() { _sprite->Render(_frames[_currentFrame]); }

void Animations::SpriteAnimation::Stop() {
  if (_stopwatch != nullptr) {
    _stopwatch->Stop();
  }
}

void Animations::SpriteAnimation::Start() {
  if (!_started) {
    // _stopwatch.reset(); Not sure if memory leak or not....
    _stopwatch = CreateScope<CoffeeMaker::StopWatch>(_durationPerFrame);
    _currentFrame = 0;
    _started = true;
    _stopwatch->Start();
  }
}

void Animations::SpriteAnimation::Pause() {
  if (_stopwatch != nullptr) {
    _stopwatch->Pause();
  }
}

void Animations::SpriteAnimation::Unpause() {
  if (_stopwatch != nullptr) {
    _stopwatch->Unpause();
  }
}

void Animations::SpriteAnimation::OnComplete(std::function<void(void)> callback) { _onCompleteCallback = callback; }
