#include "Game/Echelon.hpp"

Echelon::Echelon() :
    _height(0),
    _width(0),
    _spacing(0),
    _position(Vec2{0.0f, 0.0f}),
    _speed(150.0f),
    _movementState(Echelon::MovementState::ShiftingRight) {}

Echelon::~Echelon() {}

Uint32 Echelon::GetHeight() { return _height; }
Uint32 Echelon::GetSpacing() { return _spacing; }
Uint32 Echelon::GetWidth() { return _width; }

void Echelon::Update(float) {
  switch (_movementState) {
    case Echelon::MovementState::ShiftingLeft: {
    } break;
    case Echelon::MovementState::ShiftingRight: {
    } break;
    default: {
      // Do nothing...
    } break;
  }
}
