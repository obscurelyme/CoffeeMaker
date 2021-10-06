
#ifndef _coffeemaker_coffeemakershapesrect_hpp
#define _coffeemaker_coffeemakershapesrect_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoffeeMakerShapesRect : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoffeeMakerShapesRect);
  CPPUNIT_TEST(testDefaultConstructor);
  CPPUNIT_TEST(testHeightWidthConstructor);
  CPPUNIT_TEST(testExplicitDimensionsConstructor);
  CPPUNIT_TEST(testDefaultColor);
  CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void testDefaultConstructor();
    void testHeightWidthConstructor();
    void testExplicitDimensionsConstructor();
    void testDefaultColor();
};

#endif
