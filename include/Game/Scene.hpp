#ifndef _scene_hpp
#define _scene_hpp

#include <array>
#include <string>
#include <vector>

#include "Game/Entity.hpp"
#include "Game/Tiles.hpp"

class Scene {
  public:
  Scene();
  ~Scene();

  void Render();
  void Update();
  void Init();
  void Destroy();

  private:
  Tiles* _backgroundTiles;
  std::vector<Entity*> _entities;
  std::string _id;

  static int _sceneId;
};

class SceneManager {
  public:
  void LoadScene(int sceneIndex);
  std::array<Scene* const, 2> scenes;

  private:
  int _currentSceneIndex;
};

#endif
