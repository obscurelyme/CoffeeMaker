#include "Game/Collider.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "Color.hpp"

int Collider::_colliderId = 0;
std::vector<Collider*> Collider::_colliders = {};

void Collider::PhysicsUpdate() {
  for (auto& collider : _colliders) {
    if (collider->active) {
      collider->CheckForCollision();
    }
  }
}

Collider::Collider(bool active): active(active) {
  _id = ++_colliderId;
  _colliders.emplace_back(this);
  _texture.SetColor(CoffeeMaker::Color(0, 255, 0, 255));
  clientRect.x = 0;
  clientRect.y = 0;
  clientRect.h = 32;
  clientRect.w = 32;
}

Collider::~Collider() {

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
  CM_LOGGER_INFO("Collider {} Collided with Collider: {}", _id, collider->_id);
}

void Collider::CheckForCollision() {
  for (auto&& collider : _colliders) {
    // NOTE: fitler out self
    if (collider->_id != _id && collider->active) {
      if (_AxisAlignedBoundingBoxHit(collider)) {
        OnCollision(collider);
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
  _texture.Render(clientRect.y, clientRect.x);
}
