#ifndef _testanimations_hpp
#define _testanimations_hpp

#include <SDL2/SDL.h>

#include "Game/Animations/SpriteAnimation.hpp"
#include "Game/Scene.hpp"
#include "Utilities.hpp"

class TestAnimations : public Scene {
  public:
  TestAnimations();
  virtual void Render() override;
  virtual void Update(float deltaTime) override;
  virtual void Init() override;
  virtual void Destroy() override;
  virtual void Pause() override;
  virtual void Unpause() override;
  virtual void OnEvent(Sint32 type, void* data1 = nullptr, void* data2 = nullptr) override;

  private:
  SDL_Color _backgroundColor;
  Ref<CoffeeMaker::Sprite> _sprite;
  Ref<Animations::SpriteAnimation> _explosiveAnimation;
  bool _paused;
};

#endif
