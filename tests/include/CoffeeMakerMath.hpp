
#ifndef _coffeemaker_coffeemakermath_hpp
#define _coffeemaker_coffeemakermath_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math.hpp"

class CoffeeMakerMath : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerMath);
  CPPUNIT_TEST(testFloatingPointLerp);
  CPPUNIT_TEST(testVector2DLerp);
  CPPUNIT_TEST(testVector2D);
  CPPUNIT_TEST(testVector2DUp);
  CPPUNIT_TEST(testVector2DDown);
  CPPUNIT_TEST(testVector2DLeft);
  CPPUNIT_TEST(testVector2DRight);
  CPPUNIT_TEST(testVector2DAdd);
  CPPUNIT_TEST(testVector2DDirection);
  CPPUNIT_TEST(testVector2DMagnitude);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();
  void testFloatingPointLerp();
  void testVector2DLerp();
  void testVector2D();
  void testVector2DUp();
  void testVector2DDown();
  void testVector2DLeft();
  void testVector2DRight();
  void testVector2DAdd();
  void testVector2DDirection();
  void testVector2DMagnitude();
};

#endif
