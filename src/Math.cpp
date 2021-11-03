#include "Math.hpp"

#include <cmath>

RNG CoffeeMaker::Math::RandomEngine::engine;

float CoffeeMaker::Math::Random(float min, float max) {
  std::uniform_real_distribution<float> distro{min, max};
  return distro(CoffeeMaker::Math::RandomEngine::engine);
}

float CoffeeMaker::Math::Lerp(float f1, float f2, float t) { return (1 - t) * f1 + t * f2; }

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Lerp(const CoffeeMaker::Math::Vector2D& v1,
                                                    const CoffeeMaker::Math::Vector2D& v2, float t) {
  return CoffeeMaker::Math::Vector2D(CoffeeMaker::Math::Lerp(v1.x, v2.x, t), CoffeeMaker::Math::Lerp(v1.y, v2.y, t));
}

float CoffeeMaker::Math::InverseLerp(float f1, float f2, float value) { return (value - f1) / (f2 - value); }

float CoffeeMaker::Math::Remap(float inputMin, float inputMax, float outputMin, float outputMax, float value) {
  float weight = CoffeeMaker::Math::InverseLerp(inputMin, inputMax, value);
  return CoffeeMaker::Math::Lerp(outputMin, outputMax, weight);
}

float CoffeeMaker::Math::rad2deg(float rad) { return rad * static_cast<float>(180.0f / M_PI); }

float CoffeeMaker::Math::deg2rad(float deg) { return deg * static_cast<float>(M_PI / 180.0f); }

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::QuadraticBezierCurve(const CoffeeMaker::Math::Vector2D& startPos,
                                                                    const CoffeeMaker::Math::Vector2D& centralPoint,
                                                                    const CoffeeMaker::Math::Vector2D& endPos,
                                                                    float t) {
  CoffeeMaker::Math::Vector2D lerpA = CoffeeMaker::Math::Lerp(startPos, centralPoint, t);
  CoffeeMaker::Math::Vector2D lerpB = CoffeeMaker::Math::Lerp(centralPoint, endPos, t);
  return CoffeeMaker::Math::Lerp(lerpA, lerpB, t);
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::CubicBezierCurve(const CoffeeMaker::Math::Vector2D& startPos,
                                                                const CoffeeMaker::Math::Vector2D& midPointA,
                                                                const CoffeeMaker::Math::Vector2D& midPointB,
                                                                const CoffeeMaker::Math::Vector2D& endPos, float t) {
  CoffeeMaker::Math::Vector2D lerpA = CoffeeMaker::Math::Lerp(startPos, midPointA, t);
  CoffeeMaker::Math::Vector2D lerpB = CoffeeMaker::Math::Lerp(midPointA, midPointB, t);
  CoffeeMaker::Math::Vector2D lerpC = CoffeeMaker::Math::Lerp(midPointB, endPos, t);
  CoffeeMaker::Math::Vector2D lerpD = CoffeeMaker::Math::Lerp(lerpA, lerpB, t);
  CoffeeMaker::Math::Vector2D lerpE = CoffeeMaker::Math::Lerp(lerpB, lerpC, t);
  return CoffeeMaker::Math::Lerp(lerpD, lerpE, t);
}

CoffeeMaker::Math::Vector2D::Vector2D(float xx, float yy) : x(xx), y(yy) {}

CoffeeMaker::Math::Vector2D::Vector2D(const CoffeeMaker::Math::Vector2D& rhs) : x(rhs.x), y(rhs.y) {}

CoffeeMaker::Math::Vector2D& CoffeeMaker::Math::Vector2D::operator+=(const CoffeeMaker::Math::Vector2D& rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

CoffeeMaker::Math::Vector2D& CoffeeMaker::Math::Vector2D::operator-=(const CoffeeMaker::Math::Vector2D& rhs) {
  x -= rhs.x;
  y -= rhs.y;
  return *this;
}

CoffeeMaker::Math::Vector2D& CoffeeMaker::Math::Vector2D::operator*=(float scalar) {
  x *= scalar;
  y *= scalar;
  return *this;
}

bool CoffeeMaker::Math::Vector2D::operator==(const Vector2D& rhs) {
  if (this == &rhs) return true;
  return x == rhs.x && y == rhs.y;
}

CoffeeMaker::Math::Vector2D& CoffeeMaker::Math::Vector2D::operator=(const Vector2D& rhs) {
  x = rhs.x;
  y = rhs.y;
  return *this;
}

float CoffeeMaker::Math::Vector2D::Dot(const CoffeeMaker::Math::Vector2D& rhs) const {
  return (x * rhs.x) + (y * rhs.y);
}

float CoffeeMaker::Math::Vector2D::AngleBetween(const CoffeeMaker::Math::Vector2D& rhs) const {
  float d = this->Dot(rhs);
  float magA = this->Magnitude();
  float magB = rhs.Magnitude();
  return std::acos(d / (magA * magB));
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Rotate(float degrees) const {
  // NOTE: idk if this is correct...
  // x2=cosβx1−sinβy1
  // y2=sinβx1+cosβy1
  float x2 = (std::cos(degrees) * this->x) - (std::sin(degrees) * this->y);
  float y2 = (std::sin(degrees) * this->x) + (std::cos(degrees) * this->y);
  return CoffeeMaker::Math::Vector2D(x2, y2);
}

float CoffeeMaker::Math::Vector2D::Direction(const CoffeeMaker::Math::Vector2D& rhs) {
  return std::atan((y - rhs.y) / (x - rhs.x));
}

float CoffeeMaker::Math::Vector2D::LookAt(const CoffeeMaker::Math::Vector2D& rhs) {
  float arcTan = std::atan((y - rhs.y) / (x - rhs.x));

  if (rhs.y - y < 0 && rhs.x - x < 0) {
    arcTan += static_cast<float>(M_PI);
  } else if (rhs.x - x < 0) {
    arcTan += static_cast<float>(M_PI);
  }

  return arcTan;
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::HeadTowards(const CoffeeMaker::Math::Vector2D& rhs) {
  float xx = rhs.x - x;
  float yy = rhs.y - y;
  return CoffeeMaker::Math::Normalize(CoffeeMaker::Math::Vector2D{xx, yy});
}

float CoffeeMaker::Math::Vector2D::Magnitude(const CoffeeMaker::Math::Vector2D& rhs) const {
  return static_cast<float>(std::sqrt(std::pow(rhs.x - x, 2) + std::pow(rhs.y - y, 2)));
}

float CoffeeMaker::Math::Vector2D::Magnitude(float endX, float endY) const {
  return static_cast<float>(std::sqrt(std::pow(endX - x, 2) + std::pow(endY - y, 2)));
}

float CoffeeMaker::Math::Vector2D::Magnitude(void) const {
  return static_cast<float>(std::sqrt(std::pow(x, 2) + std::pow(y, 2)));
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Up() { return CoffeeMaker::Math::Vector2D(0, 1); }
CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Down() { return CoffeeMaker::Math::Vector2D(0, -1); }
CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Left() { return CoffeeMaker::Math::Vector2D(-1, 0); }
CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Right() { return CoffeeMaker::Math::Vector2D(1, 0); }

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Normalize(const CoffeeMaker::Math::Vector2D& vector) {
  float magnitude = vector.Magnitude();
  if (magnitude == 0) {
    return CoffeeMaker::Math::Vector2D(0, 0);
  }
  return CoffeeMaker::Math::Vector2D(vector.x / magnitude, vector.y / magnitude);
}
