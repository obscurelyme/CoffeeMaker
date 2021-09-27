#include "Transform.hpp"

Transform::Transform(float x, float y) {
  vec2.x = x;
  vec2.y = y;
}

Transform::~Transform() {}

const glm::vec2& Transform::Position() const { return vec2; }
