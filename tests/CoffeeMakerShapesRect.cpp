
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerShapesRect.hpp"
#include "Primitives/Rect.hpp"

void CoffeeMakerShapesRect::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerShapesRect::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerShapesRect::testDefaultConstructor() {
  CoffeeMaker::Shapes::Rect rect;

  CPPUNIT_ASSERT_EQUAL(0, rect.Height());
  CPPUNIT_ASSERT_EQUAL(0, rect.Width());
  CPPUNIT_ASSERT_EQUAL(0, rect.Top());
  CPPUNIT_ASSERT_EQUAL(0, rect.Left());
}

void CoffeeMakerShapesRect::testHeightWidthConstructor() {
  CoffeeMaker::Shapes::Rect rect(500, 100);

  CPPUNIT_ASSERT_EQUAL(500, rect.Height());
  CPPUNIT_ASSERT_EQUAL(100, rect.Width());
  CPPUNIT_ASSERT_EQUAL(0, rect.Top());
  CPPUNIT_ASSERT_EQUAL(0, rect.Left());
}

void CoffeeMakerShapesRect::testExplicitDimensionsConstructor() {
  CoffeeMaker::Shapes::Rect rect(500, 100, 50, 75);

  CPPUNIT_ASSERT_EQUAL(500, rect.Height());
  CPPUNIT_ASSERT_EQUAL(100, rect.Width());
  CPPUNIT_ASSERT_EQUAL(50, rect.Top());
  CPPUNIT_ASSERT_EQUAL(75, rect.Left());
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerShapesRect);

