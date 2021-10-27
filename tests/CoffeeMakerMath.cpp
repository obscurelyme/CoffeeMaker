
#include "CoffeeMakerMath.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

// #include "Game/PlayerEvents.hpp"

void CoffeeMakerMath::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerMath::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerMath::testFloatingPointLerp() {
  float f1 = 0.0f;
  float f2 = 1.0f;
  float t = 0.5f;

  CPPUNIT_ASSERT_EQUAL(CoffeeMaker::Math::Lerp(f1, f2, t), 0.5f);
}

void CoffeeMakerMath::testVector2D() {
  CoffeeMaker::Math::Vector2D vec2{1.0f, 2.0f};

  CPPUNIT_ASSERT_EQUAL(vec2.x, 1.0f);
  CPPUNIT_ASSERT_EQUAL(vec2.y, 2.0f);
}

void CoffeeMakerMath::testVector2DAdd() {
  CoffeeMaker::Math::Vector2D vec1{1.0f, 2.0f};
  CoffeeMaker::Math::Vector2D vec2{2.0f, 3.0f};

  CoffeeMaker::Math::Vector2D vec3 = vec1 + vec2;

  CPPUNIT_ASSERT_EQUAL(vec3.x, 3.0f);
  CPPUNIT_ASSERT_EQUAL(vec3.y, 5.0f);
}

void CoffeeMakerMath::testVector2DDirection() {
  CoffeeMaker::Math::Vector2D vec1{1.0f, 2.0f};
  CoffeeMaker::Math::Vector2D vec2{2.0f, 3.0f};

  float angle = CoffeeMaker::Math::rad2deg(vec1.Direction(vec2));

  CPPUNIT_ASSERT_EQUAL(angle, 45.0f);
}

void CoffeeMakerMath::testVector2DMagnitude() {
  CoffeeMaker::Math::Vector2D vec1{1.0f, 2.0f};
  CoffeeMaker::Math::Vector2D vec2{2.0f, 3.0f};

  float mag = vec1.Magnitude(vec2);

  CPPUNIT_ASSERT_EQUAL(mag, 1.0f);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerMath);
