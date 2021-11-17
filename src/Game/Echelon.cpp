#include "Game/Echelon.hpp"

float Echelon::_rightBoundary = 750;
float Echelon::_leftBoundary = 50;
unsigned int Echelon::_uid = 0;

IEchelonItem::IEchelonItem() :
    _isInEchelon(false), _echelonId(""), _echelon(nullptr), _echelonState(IEchelonItem::EchelonState::Solo) {}

void IEchelonItem::AddToEchelon(Echelon* echelon) {
  _echelonId = echelon->GetId();
  _echelonIndex = echelon->_currentIndex;
  _echelon = echelon;
}

void IEchelonItem::RemoveFromEchelon() {
  _echelon->RemoveAtIndex(_echelonIndex);
  _echelonState = IEchelonItem::EchelonState::Solo;
  _echelon = nullptr;
}

void IEchelonItem::SyncToEchelon() { _echelonState = IEchelonItem::EchelonState::Synced; }

void IEchelonItem::DesyncFromEchelon() { _echelonState = IEchelonItem::EchelonState::Solo; }

bool IEchelonItem::IsInEchelon() const { return _echelon != nullptr; }

bool IEchelonItem::IsSynced() const { return _echelonState == IEchelonItem::EchelonState::Synced; }

Echelon::Echelon(float width, float height, float spacing, float speed, const std::string& name) :
    _height(height),
    _width(width),
    _spacing(spacing),
    _position(Vec2{0.0f, 0.0f}),
    _speed(speed),
    _enemies({}),
    _movementState(Echelon::MovementState::ShiftingRight),
    _id("Echelon-" + std::to_string(++_uid)),
    _name(name),
    _currentIndex(0) {
  _enemies.fill(nullptr);
}

Echelon::~Echelon() {
  // NOTE: Echelon is NOT responsible for cleaning up Enemy instances
  // Echelon will only clear up it's own resources. It will not "own"
  // an Enemy.
  _enemies.fill(nullptr);
}

void Echelon::Add(IEchelonItem* enemy) {
  if (_currentIndex <= ECHELON_SIZE - 1) {
    enemy->AddToEchelon(this);
    _enemies[_currentIndex] = enemy;
    _currentIndex++;
  }
}

void Echelon::RemoveAtIndex(unsigned int index) {
  if (index >= 0 && index <= ECHELON_SIZE - 1) {
    _enemies[index] = nullptr;
  }
}

float Echelon::GetHeight() { return _height; }
float Echelon::GetSpacing() { return _spacing; }
float Echelon::GetWidth() { return _width; }

void Echelon::SetPosition(const Vec2& newPosition) { _position = newPosition; }

void Echelon::Update(float deltaTime) {
  switch (_movementState) {
    case Echelon::MovementState::ShiftingLeft: {
      _position += CoffeeMaker::Math::Vector2D::Left() * deltaTime * _speed;
      if (HitLeftBoundary()) {
        _movementState = Echelon::MovementState::ShiftingRight;
      }
    } break;
    case Echelon::MovementState::ShiftingRight: {
      _position += CoffeeMaker::Math::Vector2D::Right() * deltaTime * _speed;
      if (HitRightBoundary()) {
        _movementState = Echelon::MovementState::ShiftingLeft;
      }
    } break;
    default: {
      // Do nothing...
    } break;
  }

  // Update all nested enemy positions
  int index = 0;
  for (IEchelonItem* enemy : _enemies) {
    if (enemy != nullptr && enemy->IsSynced()) {
      enemy->SetEchelonPosition(_position);
    }
    index++;
  }
}

void Echelon::OnSDLUserEvent(const SDL_UserEvent&) {}

bool Echelon::HitRightBoundary() const {
  // Get sum of width + spacing of child elements
  float w = 0.0f;
  for (IEchelonItem* enemy : _enemies) {
    w += enemy->GetEchelonSpace();
  }
  w += _spacing * ECHELON_SIZE;
  return _position.x + w >= _rightBoundary;
}

bool Echelon::HitLeftBoundary() const { return _position.x <= _leftBoundary; }
