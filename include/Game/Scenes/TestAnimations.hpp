#ifndef _testanimations_hpp
#define _testanimations_hpp

#include <SDL2/SDL.h>

#include "Game/Animations/SpriteAnimation.hpp"
#include "Game/Scene.hpp"
#include "Utilities.hpp"

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
  bool _paused;
};

#endif
