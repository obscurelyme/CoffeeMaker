#ifndef _mainscene_hpp
#define _mainscene_hpp

#include <array>

#include "Audio.hpp"
#include "Game/Enemy.hpp"
#include "Game/Entity.hpp"
#include "Game/Hud.hpp"
#include "Game/Menus/Menu.hpp"
#include "Game/Player.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

class MainScene : public Scene {
  public:
  MainScene();
  virtual void Render();
  virtual void Update(float deltaTime);
  virtual void Init();
  virtual void Destroy();
  virtual void Pause();
  virtual void Unpause();

  private:
  void SpawnEnemy();

  static const unsigned int MAX_ENEMIES = 5;

  Tiles* _backgroundTiles;
  Player* _player;
  Enemy* _specialEnemy;
  std::array<Ref<Enemy>, MAX_ENEMIES> _enemies;
  std::vector<Entity*> _entities;
  Menu* _menu;
  HeadsUpDisplay* _hud;
  CoffeeMaker::Timer _timer;
  Scope<CoffeeMaker::Timeout> _enemyTimeoutSpawn;
  unsigned int _currentSpawn{0};
  CoffeeMaker::MusicTrack* _music;
};

#endif
