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
  enum class Type { Friendly, Hostile };
  enum class Size { Large, Small };
  Projectile();
  explicit Projectile(Collider::Type colliderType);
  Projectile(Collider::Type colliderType, Projectile::Type type, Projectile::Size size);
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
  static Ref<CoffeeMaker::Texture> _laserSmallRed;
  static Ref<CoffeeMaker::Texture> _laserSmallGreen;
  static Ref<CoffeeMaker::Texture> _laserLargeRed;
  static Ref<CoffeeMaker::Texture> _laserLargeGreen;
  static Ref<CoffeeMaker::Texture> _standardMissile;
  static Ref<CoffeeMaker::AudioElement> _fireSound;
  static Ref<CoffeeMaker::AudioElement> _impactSound;

  Ref<CoffeeMaker::Texture> _texture;
  bool _fired;
  SDL_FRect _clientRect;
  double _rotation;
  float _endX;
  float _endY;
  glm::vec2 _movement;
  Collider* collider;
  float _speed;
};

#endif
