#include "Game/Scenes/MainScene.hpp"

#include "InputManager.hpp"

void MainScene::Render() {
  _backgroundTiles->Render();
  for (auto& entity : _entities) {
    entity->Render();
  }

  _menu->Render();
}

void MainScene::Update() {
  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
    if (_menu->IsShown()) {
      _menu->Hide();
    } else {
      _menu->Show();
    }
  }

  for (auto& entity : _entities) {
    entity->Update();
  }
}

void MainScene::Init() {
  _menu->Init();
  _backgroundTiles = new Tiles("space.png", 800, 600);
  Player* p = new Player();
  Enemy* enemy = new Enemy();

  _entities.push_back(p);
  _entities.push_back(enemy);
}

void MainScene::Destroy() { _entities.clear(); }

MainScene::MainScene() : _menu(std::make_unique<Menu>()) {}
