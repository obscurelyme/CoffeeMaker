#ifndef _titlescene_hpp
#define _titlescene_hpp

#include <memory>

#include "Audio.hpp"
#include "Game/Scene.hpp"
#include "Utilities.hpp"
#include "Widgets/All.hpp"

class TitleScene : public Scene {
  public:
  virtual void Render() override;
  virtual void Update(float deltaTime) override;
  virtual void Init() override;
  virtual void Destroy() override;
  virtual void Pause() override;
  virtual void Unpause() override;

  void Play();
  void Quit();

  private:
  SDL_Color _backgroundColor;
  std::vector<Ref<CoffeeMaker::UIComponent>> _entities;
  CoffeeMaker::MusicTrack* _music;
};

#endif
