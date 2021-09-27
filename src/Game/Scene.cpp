#include "Game/Scene.hpp"

#include "Game/Enemy.hpp"
#include "Game/Player.hpp"

int Scene::_sceneId = 0;

Scene::Scene() { _id = "Scene-" + std::to_string(++_sceneId); }

Scene::~Scene() {}

void Scene::Render() {
  _backgroundTiles->Render();
  for (auto& entity : _entities) {
    entity->Render();
  }
}

void Scene::Update() {
  for (auto& entity : _entities) {
    entity->Update();
  }
}

void Scene::Init() {
  _backgroundTiles = new Tiles("space.png", 800, 600);
  Player* p = new Player();
  Enemy* enemy = new Enemy();

  _entities.push_back(p);
  _entities.push_back(enemy);
}

void Scene::Destroy() { _entities.clear(); }
