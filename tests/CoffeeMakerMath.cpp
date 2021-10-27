
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

void CoffeeMakerMath::testVector2DLerp() {
  CoffeeMaker::Math::Vector2D vec =
      CoffeeMaker::Math::Lerp(CoffeeMaker::Math::Vector2D::Up(), CoffeeMaker::Math::Vector2D::Right(), 0.75f);

  CPPUNIT_ASSERT_EQUAL(vec.x, 0.75f);
  CPPUNIT_ASSERT_EQUAL(vec.y, 0.25f);
}

void CoffeeMakerMath::testVector2D() {
  CoffeeMaker::Math::Vector2D vec2{1.0f, 2.0f};

  CPPUNIT_ASSERT_EQUAL(vec2.x, 1.0f);
  CPPUNIT_ASSERT_EQUAL(vec2.y, 2.0f);
}

void CoffeeMakerMath::testVector2DUp() {
  CoffeeMaker::Math::Vector2D vec2 = CoffeeMaker::Math::Vector2D::Up();

  CPPUNIT_ASSERT_EQUAL(vec2.x, 0.0f);
  CPPUNIT_ASSERT_EQUAL(vec2.y, 1.0f);
}

void CoffeeMakerMath::testVector2DDown() {
  CoffeeMaker::Math::Vector2D vec2 = CoffeeMaker::Math::Vector2D::Down();

  CPPUNIT_ASSERT_EQUAL(vec2.x, 0.0f);
  CPPUNIT_ASSERT_EQUAL(vec2.y, -1.0f);
}

void CoffeeMakerMath::testVector2DLeft() {
  CoffeeMaker::Math::Vector2D vec2 = CoffeeMaker::Math::Vector2D::Left();

  CPPUNIT_ASSERT_EQUAL(vec2.x, -1.0f);
  CPPUNIT_ASSERT_EQUAL(vec2.y, 0.0f);
}

void CoffeeMakerMath::testVector2DRight() {
  CoffeeMaker::Math::Vector2D vec2 = CoffeeMaker::Math::Vector2D::Right();

  CPPUNIT_ASSERT_EQUAL(vec2.x, 1.0f);
  CPPUNIT_ASSERT_EQUAL(vec2.y, 0.0f);
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
  float remainder = mag - 1;
  int who = (int)(mag - remainder);

  CPPUNIT_ASSERT_EQUAL(who, 1);
  CPPUNIT_ASSERT_EQUAL(remainder, 1.0f);
}

void CoffeeMakerMath::testVector2DAssignmentOverload() {
  CoffeeMaker::Math::Vector2D vec1{5.0f, 10.0f};
  CoffeeMaker::Math::Vector2D vec2 = vec1;

  CPPUNIT_ASSERT_EQUAL(&vec1 == &vec2, false);
  CPPUNIT_ASSERT_EQUAL(vec2.x, vec1.x);
  CPPUNIT_ASSERT_EQUAL(vec2.y, vec1.y);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerMath);
