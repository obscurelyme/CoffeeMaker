#ifndef _testanimations_hpp
#define _testanimations_hpp

#include <SDL2/SDL.h>

#include <string>

#include "Async.hpp"
#include "Game/Animations/SpriteAnimation.hpp"
#include "Game/Scene.hpp"
#include "Logger.hpp"
#include "Math.hpp"
#include "Utilities.hpp"
#include "Widgets/Text.hpp"

class TestAnimations : public Scene {
  public:
  TestAnimations();
  virtual void Render();
  virtual void Update(float deltaTime);
  virtual void Init();
  virtual void Destroy();
  virtual void Pause();
  virtual void Unpause();

  virtual void OnSDLUserEvent(const SDL_UserEvent& event);

  private:
  SDL_Color _backgroundColor;
  Ref<CoffeeMaker::Sprite> _sprite;
  Ref<Animations::SpriteAnimation> _explosiveAnimation;
  Scope<CoffeeMaker::Math::Oscillate> _osc;
  Scope<CoffeeMaker::Widgets::Text> _oscText;
  Scope<CoffeeMaker::Async::IntervalTask> _task;
  bool _paused;
  float _delta{0.0f};
  std::string _ttt{"0"};
  Uint8 _cVal{255};
};

#endif
