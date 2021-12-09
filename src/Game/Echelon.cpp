#include "Game/Echelon.hpp"

#include "Renderer.hpp"

float Echelon::_rightBoundary = 0.0f;
float Echelon::_leftBoundary = 50.0f;
unsigned int Echelon::_uid = 0;

EchelonItem::EchelonItem() :
    _isInEchelon(false), _echelonId(""), _echelon(nullptr), _echelonState(EchelonItem::EchelonState::Solo) {}

void EchelonItem::AddToEchelon(Echelon* echelon) {
  _echelonId = echelon->GetId();
  _echelonIndex = echelon->_currentIndex;
  _echelon = echelon;
}

void EchelonItem::RemoveFromEchelon() {
  _echelon->RemoveAtIndex(_echelonIndex);
  _echelonState = EchelonItem::EchelonState::Solo;
  _echelon = nullptr;
}

void EchelonItem::SyncToEchelon() { _echelonState = EchelonItem::EchelonState::Synced; }

void EchelonItem::DesyncFromEchelon() { _echelonState = EchelonItem::EchelonState::Solo; }

bool EchelonItem::IsInEchelon() const { return _echelon != nullptr; }

bool EchelonItem::IsSynced() const { return _echelonState == EchelonItem::EchelonState::Synced; }

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
  if (_rightBoundary == 0.0f) {
    _rightBoundary = CoffeeMaker::Renderer::GetOutputWidth() - 50.0f;
  }
  _speed *= CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _spacing *= CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _width *= CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _height *= CoffeeMaker::Renderer::DynamicResolutionDownScale();
  _enemies.fill(nullptr);
}

Echelon::~Echelon() {
  // NOTE: Echelon is NOT responsible for cleaning up Enemy instances
  // Echelon will only clear up it's own resources. It will not "own"
  // an Enemy.
  _enemies.fill(nullptr);
}

void Echelon::Add(EchelonItem* enemy) {
  if (_currentIndex <= ECHELON_SIZE - 1) {
    enemy->AddToEchelon(this);
    _enemies[_currentIndex] = enemy;
    _currentIndex++;
  }
}

void Echelon::RemoveAtIndex(unsigned int index) {
  if (index <= ECHELON_SIZE - 1) {
    _enemies[index] = nullptr;
  }
}

float Echelon::GetHeight() { return _height; }
float Echelon::GetSpacing() { return _spacing; }
float Echelon::GetWidth() { return _width; }

CoffeeMaker::Math::Vector2D Echelon::GetPosition() { return _position; }

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
  for (EchelonItem* enemy : _enemies) {
    if (enemy != nullptr && enemy->IsSynced()) {
      enemy->SetEchelonPosition(_position);
    }
    index++;
  }
}

void Echelon::OnSDLUserEvent(const SDL_UserEvent&) {}

bool Echelon::HitRightBoundary() const {
  // NOTE: use static width, don't try to use dynamic width because an enemy may be removed.
  // float w = 0.0f;
  // for (IEchelonItem* enemy : _enemies) {
  //   if (e)
  //   w += enemy->GetEchelonSpace();
  // }
  // w += _spacing * ECHELON_SIZE;
  return _position.x + _width >= _rightBoundary;
}

bool Echelon::HitLeftBoundary() const { return _position.x <= _leftBoundary; }
