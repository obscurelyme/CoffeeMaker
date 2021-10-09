#ifndef _collider_hpp
#define _collider_hpp

#include <SDL2/sdl.h>

#include <functional>
#include <vector>

#include "Texture.hpp"

class Collider {
  public:
  enum class Type { Default, Projectile, Enemy, Player };
  static void PhysicsUpdate();

  Collider(Type type = Type::Default, bool active = true);
  ~Collider();

  void Update(const SDL_FRect& position);
  void OnCollision(Collider* collider);
  void OnCollide(std::function<void(Collider*)> callback);

  // Render the collider for debugging purposes
  void Render();

  void SetWidth(float w);
  void SetHeight(float h);
  Type GetType() const;

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
