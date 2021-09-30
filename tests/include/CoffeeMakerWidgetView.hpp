
#ifndef _coffeemaker_coffeemakerwidgetview_hpp
#define _coffeemaker_coffeemakerwidgetview_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestBed.hpp"

class CoffeeMakerWidgetView : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerWidgetView);
  CPPUNIT_TEST(testDefaultViewport);
  CPPUNIT_TEST(testCentered);
  CPPUNIT_TEST(testRightBottomAligned);
  CPPUNIT_TEST(testNestedAligned);
  CPPUNIT_TEST(testOutOfOrderNestedAligned);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testDefaultViewport();
  void testCentered();
  void testRightBottomAligned();
  void testNestedAligned();
  void testOutOfOrderNestedAligned();

  private:
  CoffeeMaker::Test::TestBed *_testBed;
};

#endif
