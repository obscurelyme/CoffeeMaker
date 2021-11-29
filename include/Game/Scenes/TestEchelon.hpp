#ifndef _testechelonscene_hpp
#define _testechelonscene_hpp

#include <vector>

#include "Async.hpp"
#include "Game/Echelon.hpp"
#include "Game/Enemy.hpp"
#include "Game/Events.hpp"
#include "Game/Player.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Logger.hpp"
#include "Utilities.hpp"

class TestEchelonScene : public Scene {
  public:
  TestEchelonScene();
  ~TestEchelonScene();
  virtual void Render();
  virtual void Update(float deltaTime);
  virtual void Init();
  virtual void Destroy();
  virtual void Pause();
  virtual void Unpause();

  virtual void OnSDLUserEvent(const SDL_UserEvent& event);

  private:
  void SpawnEchelonItem();

  Scope<Tiles> _backgroundTiles;
  Scope<Echelon> _echelon;
  Scope<Echelon> _echelon2;
  Scope<Echelon> _echelon3;
  std::vector<EchelonEnemy*> _enemies;
  Scope<Player> _player;
  unsigned int _currentSpawnIndex;
  std::vector<Ref<CoffeeMaker::Async::TimeoutTask>> _loadsOfTimeouts;
  Scope<CoffeeMaker::Async::TimeoutTask> _clearTimeouts;
};

#endif
