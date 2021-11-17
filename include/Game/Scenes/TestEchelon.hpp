#ifndef _testechelonscene_hpp
#define _testechelonscene_hpp

#include <vector>

#include "Game/Echelon.hpp"
#include "Game/Enemy.hpp"
#include "Game/Events.hpp"
#include "Game/Player.hpp"
#include "Game/Scene.hpp"
#include "Game/Tiles.hpp"
#include "Logger.hpp"
#include "Utilities.hpp"

class EchelonEnemy : public Enemy, public IEchelonItem {
  using Vec2 = CoffeeMaker::Math::Vector2D;

  public:
  EchelonEnemy() {
    _entranceSpline->OnComplete([this](void*) {
      // NOTE: sync with the echelon once we've entered the scene
      _echelonState = IEchelonItem::EchelonState::Synced;
    });

    _exitTimeoutTask = CreateScope<CoffeeMaker::Async::TimeoutTask>(
        "[ENEMY][EXIT-TIMEOUT-TASK] - " + _id,
        [this] {
          _echelonState = IEchelonItem::EchelonState::Solo;
          CoffeeMaker::PushEvent(UCI::Events::ENEMY_BEGIN_EXIT, this);
        },
        12000);
  }
  virtual ~EchelonEnemy() = default;

  virtual void Update(float deltaTime) {
    if (_echelonState == IEchelonItem::EchelonState::Synced) {
      // Synced state stuff
      _sprite->rotation = 180;
      _sprite->SetPosition(_position);
      _collider->Update(_sprite->clientRect);

      for (auto& projectile : _projectiles) {
        projectile->Update(deltaTime);
      }
    }
    if (_echelonState == IEchelonItem::EchelonState::Solo) {
      // Solo state stuff
      Enemy::Update(deltaTime);
    }
  }

  virtual void SetEchelonPosition(const Vec2& echelonPosition) {
    _position.x = echelonPosition.x + (GetEchelonSpace() * static_cast<float>(_echelonIndex)) +
                  (_echelon->GetSpacing() * static_cast<float>(_echelonIndex));
    _position.y = echelonPosition.y;
  }
  virtual float GetEchelonSpace() { return _sprite->clientRect.w; }

  virtual void OnSDLUserEvent(const SDL_UserEvent& event) {
    if (event.code == UCI::Events::ENEMY_DESTROYED && event.data1 == this) {
      _echelonState = IEchelonItem::EchelonState::Solo;
    }

    Enemy::OnSDLUserEvent(event);
  }
};

class TestEchelonScene : public Scene {
  public:
  TestEchelonScene();
  ~TestEchelonScene();
  virtual void Render();
  virtual void Update(float deltaTime);
  virtual void Init();
  virtual void Destroy();
  virtual void Pause();
  virtual void Unpause();

  virtual void OnSDLUserEvent(const SDL_UserEvent& event);

  private:
  void SpawnEchelonItem();

  Scope<Tiles> _backgroundTiles;
  Scope<Echelon> _echelon;
  Scope<Echelon> _echelon2;
  Scope<Echelon> _echelon3;
  std::vector<EchelonEnemy*> _enemies;
  Scope<Player> _player;
  unsigned int _currentSpawnIndex;
};

#endif
