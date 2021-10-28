#include "Game/Scenes/MainScene.hpp"

#include <SDL2/SDL.h>

#include "Event.hpp"
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

  // _specialEnemy->Render();

  _hud->Render();
  _menu->Render();
}

void MainScene::Pause() {
  SDL_ShowCursor(SDL_ENABLE);
  _hud->Pause();
  for (auto& entity : _entities) {
    entity->Pause();
  }
}

void MainScene::Unpause() {
  SDL_ShowCursor(SDL_DISABLE);
  _hud->Unpause();
  for (auto& entity : _entities) {
    entity->Unpause();
  }
}

void MainScene::Update(float deltaTime) {
  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
    if (_menu->IsShown()) {
      CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE);
      _menu->Hide();
    } else {
      CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE);
      _menu->Show();
    }
  }

  _backgroundTiles->Update(deltaTime);

  if (_currentSpawn < MAX_ENEMIES) {
    _currentTime += deltaTime;
    if (_currentTime >= _totalTime) {
      _enemies[_currentSpawn++]->Spawn();
      _currentTime = 0;
    }
  }

  for (auto enemy : _enemies) {
    // if (!enemy->IsActive()) {
    //   enemy->Spawn();
    // }
    enemy->Update(deltaTime);
  }

  // if (!_specialEnemy->IsActive()) {
  //   _specialEnemy->Spawn();
  // }
  // _specialEnemy->Update(deltaTime);

  for (auto& entity : _entities) {
    entity->Update(deltaTime);
  }

  _hud->Update();
}

void MainScene::Init() {
  SDL_ShowCursor(SDL_DISABLE);
  _hud = new HeadsUpDisplay();
  _menu = new Menu();
  _menu->Init();
  _backgroundTiles = new Tiles("space.png", 800, 600);
  _player = new Player();
  _specialEnemy = new SpecialEnemy();
  _specialEnemy->Init();

  for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
    _enemies[i] = std::make_shared<SpecialEnemy>();
    _enemies[i]->Init();
  }

  _entities.push_back(_player);
  _timer.Start();
}

void MainScene::Destroy() {
  _entities.clear();
  _enemies.fill(nullptr);
  Collider::ClearAllUnprocessedCollisions();
  delete _backgroundTiles;
  delete _player;
  delete _menu;
  delete _hud;
  delete _specialEnemy;
  _currentSpawn = 0;
  _currentTime = 0;
}

MainScene::MainScene() {}
