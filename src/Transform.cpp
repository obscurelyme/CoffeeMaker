#include "Transform.hpp"

Transform::Transform(int x, int y) {
  vec2.x = x;
  vec2.y = y;
}

Transform::~Transform() {}

const glm::vec2& Transform::Position() const {
  return vec2;
}
