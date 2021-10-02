#include "Game/Enemy.hpp"
#include "Game/Entity.hpp"
#include "Game/Menus/Menu.hpp"
#include "Game/Player.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"

class MainScene : public Scene {
  public:
  MainScene();
  virtual void Render();
  virtual void Update();
  virtual void Init();
  virtual void Destroy();

  private:
  Tiles* _backgroundTiles;
  std::vector<Entity*> _entities;
  std::unique_ptr<Menu> _menu;
};
