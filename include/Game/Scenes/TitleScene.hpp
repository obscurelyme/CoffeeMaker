#include "Game/Entity.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Widgets/UIComponent.hpp"

class MainScene : public Scene {
  public:
  virtual void Render();
  virtual void Update();
  virtual void Init();
  virtual void Destroy();

  private:
  Tiles* _backgroundTiles;
  std::vector<UIComponent*> _entities;
};
