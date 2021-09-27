#include "Game/Scenes/MainScene.hpp"

void MainScene::Render() {
  _backgroundTiles->Render();
  for (auto& entity : _entities) {
    entity->Render();
  }
}

void MainScene::Update() {
  for (auto& entity : _entities) {
    entity->Update();
  }
}

void MainScene::Init() {
  _backgroundTiles = new Tiles("space.png", 800, 600);
  Player* p = new Player();
  Enemy* enemy = new Enemy();

  _entities.push_back(p);
  _entities.push_back(enemy);
}

void MainScene::Destroy() { _entities.clear(); }
