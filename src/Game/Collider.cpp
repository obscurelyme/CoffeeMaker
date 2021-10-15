#include "Game/Collider.hpp"

#include <functional>

#include "Color.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

int Collider::_colliderId = 0;
std::vector<Collider*> Collider::_colliders = {};
std::queue<std::function<void()>> Collider::collisionQueue = {};

void Collider::PhysicsUpdate() {
  for (auto& collider : _colliders) {
    if (collider->active) {
      collider->CheckForCollision();
    }
  }
}

void Collider::ProcessCollisions() {
  while (!collisionQueue.empty()) {
    auto handleCollision = collisionQueue.front();
    collisionQueue.pop();
    handleCollision();
  }
}

Collider::Collider(Collider::Type type, bool active) : active(active), _type(type), _id(-1) {
  _id = ++_colliderId;
  _colliders.emplace_back(this);
  _texture.SetColor(CoffeeMaker::Colors::Green);
  clientRect.x = 0;
  clientRect.y = 0;
  clientRect.h = 32;
  clientRect.w = 32;
  _listeners = {};
}

Collider::~Collider() {
  active = false;
  _listeners.clear();
  for (auto colliderIter = _colliders.begin(); colliderIter != _colliders.end();) {
    if ((*colliderIter)->_id == _id) {
      colliderIter = _colliders.erase(colliderIter);
      break;
    }
    ++colliderIter;
  }
}

void Collider::SetWidth(float w) {
  clientRect.w = w;
  _texture.SetWidth((int)w);
}

void Collider::SetHeight(float h) {
  clientRect.h = h;
  _texture.SetHeight((int)h);
}

void Collider::Update(const SDL_FRect& position) {
  if (active) {
    clientRect.x = position.x;
    clientRect.y = position.y;
    _texture.SetHeight((int)clientRect.h);
    _texture.SetWidth((int)clientRect.w);
  }
}

void Collider::OnCollision(Collider* collider) {
  for (auto listener : _listeners) {
    listener(collider);
  }
}

void Collider::CheckForCollision() {
  for (auto&& collider : _colliders) {
    // NOTE: fitler out self
    if (collider->_id != _id && collider->active) {
      if (_AxisAlignedBoundingBoxHit(collider)) {
        // OnCollision(collider);
        collisionQueue.push(std::bind(&Collider::OnCollision, this, collider));
      }
    }
  }
}

bool Collider::_AxisAlignedBoundingBoxHit(Collider* collider) const {
  return clientRect.x < collider->clientRect.x + collider->clientRect.w &&
         clientRect.x + clientRect.w > collider->clientRect.x &&

         clientRect.y < collider->clientRect.y + collider->clientRect.h &&
         clientRect.y + clientRect.h > collider->clientRect.y;
}

void Collider::Render() {
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 0, 255, 0, 255);
  SDL_RenderDrawRectF(CoffeeMaker::Renderer::Instance(), &clientRect);
}

void Collider::OnCollide(std::function<void(Collider*)> callback) { _listeners.push_back(callback); }

Collider::Type Collider::GetType() const { return _type; }
