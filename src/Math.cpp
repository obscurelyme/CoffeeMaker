#include "Math.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

float CoffeeMaker::Math::Lerp(float f1, float f2, float t) { return (1 - t) * f1 + t * f2; }

// CoffeeMaker::Math::Vector2D LerpV(const CoffeeMaker::Math::Vector2D& v1, const CoffeeMaker::Math::Vector2D& v2,
//                                   float t) {
//   return;
// }

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Lerp(const CoffeeMaker::Math::Vector2D& v1,
                                                    const CoffeeMaker::Math::Vector2D& v2, float t) {
  return CoffeeMaker::Math::Vector2D(CoffeeMaker::Math::Lerp(v1.x, v2.x, t), CoffeeMaker::Math::Lerp(v1.y, v2.y, t));
}

float CoffeeMaker::Math::rad2deg(float rad) { return rad * (180 / M_PI); }

float CoffeeMaker::Math::deg2rad(float deg) { return deg * (M_PI / 180); }

CoffeeMaker::Math::Vector2D::Vector2D(float xx, float yy) : x(xx), y(yy) {}

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

float CoffeeMaker::Math::Vector2D::Direction(const CoffeeMaker::Math::Vector2D& rhs) {
  return std::atanf((y - rhs.y) / (x - rhs.x));
}

float CoffeeMaker::Math::Vector2D::Magnitude(const CoffeeMaker::Math::Vector2D& rhs) {
  return std::sqrtf(std::powf(rhs.x - x, 2) / std::powf(rhs.y - y, 2));
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Up() { return CoffeeMaker::Math::Vector2D(0, 1); }
CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Down() { return CoffeeMaker::Math::Vector2D(0, -1); }
CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Left() { return CoffeeMaker::Math::Vector2D(-1, 0); }
CoffeeMaker::Math::Vector2D CoffeeMaker::Math::Vector2D::Right() { return CoffeeMaker::Math::Vector2D(1, 0); }
