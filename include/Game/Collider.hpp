#ifndef _collider_hpp
#define _collider_hpp

#include <SDL2/sdl.h>
#include <vector>
#include "Texture.hpp"

class Collider {

  public:
    static void PhysicsUpdate();

    Collider(bool active = true);
    ~Collider();

    void Update(const SDL_FRect& position);
    void OnCollision(Collider* collider);

    // Render the collider for debugging purposes
    void Render();

    void SetWidth(float w);
    void SetHeight(float h);

    SDL_FRect clientRect;
    bool active;

  private:
    int _id;
    static int _colliderId;
    static std::vector<Collider*> _colliders;
    CoffeeMaker::Texture _texture;
    void CheckForCollision();

    bool _AxisAlignedBoundingBoxHit(Collider* collider) const;
};

#endif
