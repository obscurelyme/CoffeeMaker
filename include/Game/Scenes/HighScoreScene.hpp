#ifndef _highscorescene_hpp
#define _highscorescene_hpp

#include "Game/Scene.hpp"
#include "Utilities.hpp"
#include "Widgets/View.hpp"

class HighScoreScene : public Scene {
  public:
  HighScoreScene();
  ~HighScoreScene() = default;

  void Init() override;
  void Update(float deltaTime) override;
  void Render() override;
  void Destroy() override;
  void Pause() override;
  void Unpause() override;

  void OnSDLUserEvent(const SDL_UserEvent&) override;

  private:
  void HandlePlayAgain();
  void HandleMainMenu();
  std::string MarkNewHighScore(int place);

  Scope<CoffeeMaker::Widgets::View> _view;

  static int WIDTH;
  static int HEIGHT;
};

#endif
