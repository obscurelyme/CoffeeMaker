#ifndef _titlescene_hpp
#define _titlescene_hpp

#include <memory>

#include "Audio.hpp"
#include "Game/Scene.hpp"
#include "Utilities.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/UIComponent.hpp"
#include "Widgets/View.hpp"

class TitleScene : public Scene {
  public:
  virtual void Render();
  virtual void Update(float deltaTime);
  virtual void Init();
  virtual void Destroy();
  virtual void Pause();
  virtual void Unpause();
  virtual void OnEvent(Sint32 type, void* data1 = nullptr, void* data2 = nullptr) override;

  void Play();
  void Quit();

  private:
  SDL_Color _backgroundColor;
  std::vector<Ref<CoffeeMaker::UIComponent>> _entities;
  CoffeeMaker::MusicTrack* _music;
};

#endif
