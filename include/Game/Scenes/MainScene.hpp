#ifndef _mainscene_hpp
#define _mainscene_hpp

#include <array>
#include <functional>
#include <mutex>
#include <thread>

#include "Async.hpp"
#include "Audio.hpp"
#include "Game/Echelon.hpp"
#include "Game/Enemy.hpp"
#include "Game/Entity.hpp"
#include "Game/Hud.hpp"
#include "Game/Menus/Menu.hpp"
#include "Game/Player.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Utilities.hpp"

class MainScene : public Scene {
  public:
  MainScene();
  virtual void Render() override;
  virtual void Update(float deltaTime) override;
  virtual void Init() override;
  virtual void Destroy() override;
  virtual void Pause() override;
  virtual void Unpause() override;

  virtual void OnSDLUserEvent(const SDL_UserEvent& event) override;

  private:
  static const unsigned int MAX_ENEMIES = 12;

  Scope<Tiles> _backgroundSmokeTiles;
  Scope<Tiles> _backgroundTiles;
  Player* _player;
  std::array<EchelonEnemy*, MAX_ENEMIES> _enemies;
  std::vector<Entity*> _entities;
  Menu* _menu;
  HeadsUpDisplay* _hud;
  unsigned int _currentSpawn{0};
  CoffeeMaker::MusicTrack* _music;
  Scope<CoffeeMaker::Async::IntervalTask> _enemySpawnTask;
  Echelon* _backEchelon;
  Echelon* _frontEchelon;
};

#endif
