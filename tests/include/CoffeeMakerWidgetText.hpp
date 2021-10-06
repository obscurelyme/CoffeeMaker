
#ifndef _coffeemaker_coffeemakerwidgettext_hpp
#define _coffeemaker_coffeemakerwidgettext_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "TestBed.hpp"

using namespace CoffeeMaker::Test;

class CoffeeMakerWidgetText : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerWidgetText);
  CPPUNIT_TEST(testCreation);
  CPPUNIT_TEST(testNestedPosition);
  CPPUNIT_TEST(testNestedPositionX2);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testCreation();
  void testNestedPosition();
  void testNestedPositionX2();

  private:
  TestBed* _testBed;
};

#endif
