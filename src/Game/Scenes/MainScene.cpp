#include "Game/Scenes/MainScene.hpp"

#include <SDL2/SDL.h>

#include <iostream>
#include <thread>

#include "Event.hpp"
#include "Game/Collider.hpp"
#include "Game/Events.hpp"
#include "Game/ScoreManager.hpp"
#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

void MainScene::Render() {
  _backgroundTiles->Render();
  _backgroundSmokeTiles->Render();
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
  _backgroundSmokeTiles->Update(deltaTime);

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
  CM_LOGGER_DEBUG("============== Initialize Main Scene ==================");
  ScoreManager::ResetScore();
  _music = CoffeeMaker::Audio::LoadMusic("music/AsTheWorldTurns.ogg");
  // CoffeeMaker::Audio::PlayMusic(_music);
  SDL_ShowCursor(SDL_DISABLE);
  _hud = new HeadsUpDisplay();
  _menu = new Menu();
  _menu->Init();
  _backgroundTiles = CreateScope<Tiles>("StarBackground-DarkBlue.png", CoffeeMaker::Renderer::GetOutputWidth(),
                                        CoffeeMaker::Renderer::GetOutputHeight(), 75.0f);
  _backgroundSmokeTiles = CreateScope<Tiles>("SpaceSmoke.png", CoffeeMaker::Renderer::GetOutputWidth(),
                                             CoffeeMaker::Renderer::GetOutputHeight(), 100.0f);
  _player = new Player();
  _frontEchelon = new Echelon(363.0f, 50.0f, CoffeeMaker::Renderer::GetOutputWidth(), 15.0f);
  _backEchelon = new Echelon(363.0f, 50.0f, CoffeeMaker::Renderer::GetOutputWidth(), 15.0f);

  _frontEchelon->SetPosition(
      CoffeeMaker::Math::Vector2D{50.0f, 175.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale()});
  _backEchelon->SetPosition(
      CoffeeMaker::Math::Vector2D{50.0f, 100.0f * CoffeeMaker::Renderer::DynamicResolutionDownScale()});

  for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
    if (i < MAX_ENEMIES / 2 - 1) {
      _enemies[i] = new EchelonEnemy();
      _frontEchelon->Add(_enemies[i]);
    } else if (i == (MAX_ENEMIES / 2) - 1) {
      CM_LOGGER_DEBUG("Kamakase");
      _enemies[i] = new Kamakase();
      _frontEchelon->Add(_enemies[i]);
    } else {
      _enemies[i] = new Drone();
      _backEchelon->Add(_enemies[i]);
    }

    _enemies[i]->Init();
    CM_LOGGER_DEBUG("Initialized Enemy: {}", i);
  }

  _entities.push_back(_player);
  _loaded = true;
  _enemySpawnTask->Start();
  CM_LOGGER_DEBUG("============== Initialized Main Scene Done ==================");
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
  _backgroundTiles.reset();
  _backgroundSmokeTiles.reset();
  delete _player;
  delete _menu;
  delete _hud;
  _currentSpawn = 0;
}

MainScene::MainScene() :
    _enemySpawnTask(CreateScope<CoffeeMaker::Async::IntervalTask>(
        [] { CoffeeMaker::PushUserEvent(UCI::Events::ENEMY_INITIAL_INTERVAL_SPAWN); }, 300)) {}

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
