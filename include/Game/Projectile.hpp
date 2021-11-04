#ifndef _projectile_hpp
#define _projectile_hpp

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <memory>

#include "Audio.hpp"
#include "Game/Collider.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"

class Projectile {
  public:
  Projectile();
  explicit Projectile(Collider::Type colliderType);
  ~Projectile();

  /**
   * @brief Fires the projectile at a calculated position based on the given rotation
   *
   * @param initialXPosition
   * @param initialYPosition
   * @param rotation
   */
  void Fire(float initialXPosition, float initialYPosition, double rotation);
  /**
   * @brief Fire function that is explicitly passed an end position.
   *
   * @param initialXPosition
   * @param initialYPosition
   * @param endX
   * @param endY
   * @param rotation
   */
  void Fire2(float initialXPosition, float initialYPosition, float endX, float endY, double rotation);
  void Reload();
  void Update(float deltaTime);
  void Render();
  bool IsOffScreen() const;
  void OnHit(Collider* collider);
  bool IsFired() const;

  private:
  static Ref<CoffeeMaker::Texture> _texture;
  static Ref<CoffeeMaker::AudioElement> _fireSound;
  static Ref<CoffeeMaker::AudioElement> _impactSound;
  bool _fired;
  SDL_FRect _clientRect;
  double _rotation;
  float _endX;
  float _endY;
  glm::vec2 _movement;
  Collider* collider;
};

#endif
