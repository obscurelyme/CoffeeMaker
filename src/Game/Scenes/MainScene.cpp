#include "Game/Scenes/MainScene.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <thread>

#include "Event.hpp"
#include "Game/Collider.hpp"
#include "Game/Events.hpp"
#include "Game/ScoreManager.hpp"
#include "InputManager.hpp"
#include "Renderer.hpp"

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

void MainScene::Pause() {
  _enemySpawnTask->Pause();
  SDL_ShowCursor(SDL_ENABLE);
  _hud->Pause();
  for (auto enemy : _enemies) {
    enemy->Pause();
  }
  for (auto& entity : _entities) {
    entity->Pause();
  }
}

void MainScene::Unpause() {
  _enemySpawnTask->Unpause();
  SDL_ShowCursor(SDL_DISABLE);
  _hud->Unpause();
  for (auto enemy : _enemies) {
    enemy->Unpause();
  }
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

  _backEchelon->Update(deltaTime);
  _frontEchelon->Update(deltaTime);

  for (auto enemy : _enemies) {
    enemy->Update(deltaTime);
  }

  for (auto& entity : _entities) {
    entity->Update(deltaTime);
  }

  _hud->Update();
}

void MainScene::Init() {
  ScoreManager::ResetScore();
  _music = CoffeeMaker::Audio::LoadMusic("music/AsTheWorldTurns.ogg");
  CoffeeMaker::Audio::PlayMusic(_music);
  SDL_ShowCursor(SDL_DISABLE);
  _hud = new HeadsUpDisplay();
  _menu = new Menu();
  _menu->Init();
  _backgroundTiles =
      new Tiles("space.png", CoffeeMaker::Renderer::GetOutputWidth(), CoffeeMaker::Renderer::GetOutputHeight());
  _player = new Player();
  _frontEchelon = new Echelon(300.0f, 50.0f, 5.0f);
  _backEchelon = new Echelon(300.0f, 50.0f, 5.0f);
  _frontEchelon->SetPosition(CoffeeMaker::Math::Vector2D{50.0f, 150.0f});
  _backEchelon->SetPosition(CoffeeMaker::Math::Vector2D{50.0f, 100.0f});

  for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
    if (i < MAX_ENEMIES / 2) {
      _enemies[i] = new EchelonEnemy();
      _frontEchelon->Add(_enemies[i]);
    } else {
      _enemies[i] = new Drone();
      _backEchelon->Add(_enemies[i]);
    }

    _enemies[i]->Init();
  }

  _entities.push_back(_player);
  _loaded = true;
  _enemySpawnTask->Start();
}

void MainScene::Destroy() {
  _loaded = false;
  _enemySpawnTask->Cancel();
  CoffeeMaker::Audio::StopMusic();
  CoffeeMaker::Audio::FreeMusic(_music);
  _entities.clear();
  for (EchelonEnemy* e : _enemies) {
    e->RemoveFromEchelon();
    delete e;
  }
  delete _frontEchelon;
  delete _backEchelon;
  _enemies.fill(nullptr);
  Collider::ClearAllUnprocessedCollisions();
  delete _backgroundTiles;
  delete _player;
  delete _menu;
  delete _hud;
  _currentSpawn = 0;
}

MainScene::MainScene() :
    _enemySpawnTask(CreateScope<CoffeeMaker::Async::IntervalTask>(
        [] { CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_INITIAL_INTERVAL_SPAWN); }, 500)) {}

void MainScene::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (_loaded) {
    switch (event.type) {
      case UCI::Events::ENEMY_INITIAL_INTERVAL_SPAWN: {
        CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_SPAWNED, -1, _enemies[_currentSpawn++]);
        if (_currentSpawn == MAX_ENEMIES) {
          _enemySpawnTask->Cancel();
        }
      } break;
      case UCI::Events::LOAD_NEW_SCENE: {
        if (event.code == 2) {
          SceneManager::LoadScene(event.code);
        }
      } break;
    }
  }
}
