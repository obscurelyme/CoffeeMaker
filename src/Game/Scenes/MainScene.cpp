#include "Game/Scenes/MainScene.hpp"

#include "Game/Collider.hpp"
#include "InputManager.hpp"

void MainScene::Render() {
  _backgroundTiles->Render();
  for (auto& entity : _entities) {
    entity->Render();
  }

  for (auto enemy : _enemies) {
    enemy->Render();
  }

  _hud->Render();
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

  for (auto enemy : _enemies) {
    if (!enemy->IsActive()) {
      enemy->Spawn();
    }
    enemy->Update();
  }

  for (auto& entity : _entities) {
    entity->Update();
  }

  _hud->Update();
}

void MainScene::Init() {
  _hud = new HeadsUpDisplay();
  _menu = new Menu();
  _menu->Init();
  _backgroundTiles = new Tiles("space.png", 800, 600);
  _player = new Player();
  // _enemies = {};

  for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
    _enemies[i] = std::make_shared<Enemy>();
  }

  _entities.push_back(_player);
}

void MainScene::Destroy() {
  _entities.clear();
  _enemies.fill(nullptr);
  Collider::ClearAllUnprocessedCollisions();
  delete _backgroundTiles;
  delete _player;
  delete _menu;
  delete _hud;
}

MainScene::MainScene() {}
