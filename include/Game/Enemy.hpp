#include <SDL2/SDL.h>

#include <functional>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "Game/Collider.hpp"
#include "Game/Entity.hpp"
#include "Game/Projectile.hpp"
#include "Math.hpp"
#include "Texture.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

class Timeout : public CoffeeMaker::Timer {
  public:
  explicit Timeout(Uint32 delay, std::function<void(void)> fn) : _delay(delay), _callback(fn), _started(false){};
  ~Timeout() = default;

  void Start() {
    if (!_started) {
      _started = true;
      CoffeeMaker::Timer::Start();
    }
  };

  bool Check() { return GetTicks() >= _delay; };

  void Act() {
    if (Check()) {
      std::invoke(_callback);
      CoffeeMaker::Timer::Stop();
      _started = false;
    }
  };

  private:
  Uint32 _delay;
  std::function<void(void)> _callback;
  bool _started;
};

class Enemy : public Entity {
  public:
  Enemy();
  virtual ~Enemy();

  virtual void Init();
  virtual void Update(float deltaTime);
  virtual void Render();
  virtual void Pause();
  virtual void Unpause();
  virtual void Fire();

  virtual void Spawn();
  bool IsActive() const;
  virtual void OnCollision(Collider* collider);
  bool IsOffScreen() const;

  protected:
  CoffeeMaker::Texture _texture{"EnemyV1.png", true};
  SDL_Rect _clipRect{.x = 0, .y = 0, .w = 32, .h = 32};
  SDL_FRect _clientRect{.x = 0, .y = 0, .w = 48, .h = 48};
  glm::vec2 _movement;
  Ref<Collider> _collider;

  bool _enteredScreen;
  bool _active;
  std::string _id;

  static unsigned int _uid;

  // EnemyAnimationState _state{EnemyAnimationState::Idle};
  unsigned int _ticks;
  unsigned int _priorTicks;
  unsigned int _speed{225};
  int _rotation{-90};
  std::vector<Projectile*> _projectiles;
  int _currentProjectile = 0;
  Timeout _to{500, std::bind(&Enemy::Fire, this)};
};

class SpecialEnemy : public Enemy {
  public:
  SpecialEnemy();
  virtual ~SpecialEnemy();

  virtual void Init() override;
  virtual void Update(float deltaTime) override;
  virtual void Render() override;
  virtual void Pause() override;
  virtual void Unpause() override;

  virtual void Spawn() override;

  protected:
  CoffeeMaker::Math::Vector2D _transformVector;
  CoffeeMaker::Math::Vector2D _endVector;
  float _totalTime{3.0f};
  float _currentTime{0.0f};
  bool _moveright{true};
};
