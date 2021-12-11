#include "Game/Scenes/TestEchelon.hpp"

#include <thread>

#include "Game/Events.hpp"
#include "InputManager.hpp"

TestEchelonScene::TestEchelonScene() :
    _backgroundTiles(CreateScope<Tiles>("space.png", 800, 600)),
    _echelon(CreateScope<Echelon>(400.0f, 50.0f, 800, 20.0f, 150.0f, "TEST_ECHELON_1")),
    _echelon2(CreateScope<Echelon>(400.0f, 50.0f, 800, 20.0f, 200.0f, "TEST_ECHELON_2")),
    _echelon3(CreateScope<Echelon>(400.0f, 50.0f, 800, 20.0f, 100.0f, "TEST_ECHELON_3")),
    _enemies({}),
    _player(nullptr),
    _currentSpawnIndex(0) {
  _echelon2->SetPosition(CoffeeMaker::Math::Vector2D{0.0f, 150.0f});
  _echelon3->SetPosition(CoffeeMaker::Math::Vector2D{0.0f, 100.0f});
  // _clearTimeouts = CreateScope<CoffeeMaker::Async::TimeoutTask>([this] { _loadsOfTimeouts.clear(); }, 2000);
  // for (int i = 0; i < 5000; i++) {
  //   auto s = CreateRef<CoffeeMaker::Async::TimeoutTask>([i] { CM_LOGGER_INFO("Done...Task - {}", i); }, 1000);
  //   _loadsOfTimeouts.push_back(s);
  //   s->Start();
  // }
  // _clearTimeouts->Start();
  CM_LOGGER_INFO("Num Threads {}", std::thread::hardware_concurrency());
}

TestEchelonScene::~TestEchelonScene() {}

void TestEchelonScene::Render() {
  _backgroundTiles->Render();
  for (EchelonEnemy* e : _enemies) {
    e->Render();
  }
  _player->Render();
}

void TestEchelonScene::Update(float deltaTime) {
  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_S)) {
    if (_currentSpawnIndex <= 14) {
      CoffeeMaker::PushEvent(UCI::Events::ENEMY_SPAWNED, _enemies[_currentSpawnIndex++]);
    }
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_ESCAPE)) {
    if (IsPaused()) {
      CoffeeMaker::PushEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE);
    } else {
      CoffeeMaker::PushEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE);
    }
  }

  // if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_1)) {
  //   if (_enemies[0]->IsSynced()) {
  //     _enemies[0]->DesyncFromEchelon();
  //   } else {
  //     _enemies[0]->SyncToEchelon();
  //   };
  // }

  // if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_2)) {
  //   if (_enemies[1]->IsSynced()) {
  //     _enemies[1]->DesyncFromEchelon();
  //   } else {
  //     _enemies[1]->SyncToEchelon();
  //   };
  // }

  // if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_3)) {
  //   if (_enemies[2]->IsSynced()) {
  //     _enemies[2]->DesyncFromEchelon();
  //   } else {
  //     _enemies[2]->SyncToEchelon();
  //   };
  // }

  // if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_4)) {
  //   if (_enemies[3]->IsSynced()) {
  //     _enemies[3]->DesyncFromEchelon();
  //   } else {
  //     _enemies[3]->SyncToEchelon();
  //   };
  // }

  // if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_5)) {
  //   if (_enemies[4]->IsSynced()) {
  //     _enemies[4]->DesyncFromEchelon();
  //   } else {
  //     _enemies[4]->SyncToEchelon();
  //   };
  // }

  _echelon->Update(deltaTime);
  _echelon2->Update(deltaTime);
  _echelon3->Update(deltaTime);
  _backgroundTiles->Update(deltaTime);
  for (Enemy* e : _enemies) {
    e->Update(deltaTime);
  }

  _player->Update(deltaTime);
}

void TestEchelonScene::Init() {
  for (int i = 0; i < 5; i++) {
    EchelonEnemy* e = new EchelonEnemy();
    e->SetAggressionState(Enemy::AggressionState::Active);
    _enemies.push_back(e);
    _echelon->Add(e);
  }
  for (int i = 5; i < 10; i++) {
    EchelonEnemy* e = new EchelonEnemy();
    e->SetAggressionState(Enemy::AggressionState::Active);
    _enemies.push_back(e);
    _echelon2->Add(e);
  }
  for (int i = 10; i < 15; i++) {
    EchelonEnemy* e = new EchelonEnemy();
    e->SetAggressionState(Enemy::AggressionState::Active);
    _enemies.push_back(e);
    _echelon3->Add(e);
  }
  _player = CreateScope<Player>();
  _player->Init();
}

void TestEchelonScene::Destroy() {
  for (EchelonEnemy* e : _enemies) {
    e->RemoveFromEchelon();
    delete e;
  }
  _enemies.clear();
  Collider::ClearAllUnprocessedCollisions();
}

void TestEchelonScene::Pause() {
  for (EchelonEnemy* e : _enemies) {
    e->Pause();
  }
}

void TestEchelonScene::Unpause() {}

void TestEchelonScene::OnSDLUserEvent(const SDL_UserEvent&) {}
