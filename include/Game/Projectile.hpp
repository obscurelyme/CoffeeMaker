#ifndef _projectile_hpp
#define _projectile_hpp

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <memory>

#include "Game/Collider.hpp"
#include "Texture.hpp"

class Projectile {
  public:
  Projectile();
  ~Projectile();

  void Fire(float initialXPosition, float initialYPosition, double rotation);
  void Reload();
  void Update(float deltaTime);
  void Render();
  bool IsOffScreen() const;
  void OnHit(Collider* collider);
  bool IsFired() const;

  private:
  static std::shared_ptr<CoffeeMaker::Texture> _texture;
  bool _fired;
  SDL_FRect _clientRect;
  double _rotation;
  float _endX;
  float _endY;
  glm::vec2 _movement;
  Collider* collider;
};

#endif
