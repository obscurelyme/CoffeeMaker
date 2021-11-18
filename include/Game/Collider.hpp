#ifndef _collider_hpp
#define _collider_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <queue>
#include <vector>

#include "Texture.hpp"

class Collider {
  public:
  enum class Type { Default, Projectile, Enemy, Player, EnemyProjectile };
  std::string ColliderTypeString(Collider::Type type) {
    switch (type) {
      case Collider::Type::Projectile:
        return "Projectile";
      case Collider::Type::Enemy:
        return "Enemy";
      case Collider::Type::Player:
        return "Player";
      case Collider::Type::EnemyProjectile:
        return "EnemyProjectile";
      default:
        return "Default";
    }
  }
  static void PhysicsUpdate();
  static void ProcessCollisions();
  /**
   * Pops all unprocessed collisions within the collision queue without processing
   * useful method for when the scene needs to be destroyed and collisions
   * no longer matter.
   */
  static void ClearAllUnprocessedCollisions();
  static std::queue<std::function<void()>> collisionQueue;

  Collider(Type type = Type::Default, bool active = false);
  ~Collider();

  void Update(const SDL_FRect& position);
  void OnCollision(Collider* collider);
  void OnCollide(std::function<void(Collider*)> callback);

  // Render the collider for debugging purposes
  void Render();

  void SetWidth(float w);
  void SetHeight(float h);
  Type GetType() const;
  void SetType(Collider::Type type);

  std::string ToString();

  SDL_FRect clientRect;
  bool active;

  private:
  Type _type;
  int _id;
  static int _colliderId;
  static std::vector<Collider*> _colliders;
  CoffeeMaker::Texture _texture;
  void CheckForCollision();
  std::vector<std::function<void(Collider*)>> _listeners;
  bool _AxisAlignedBoundingBoxHit(Collider* collider) const;
};

#endif
