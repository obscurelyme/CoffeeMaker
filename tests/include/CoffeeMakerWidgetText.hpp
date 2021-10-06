
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
<<<<<<< Updated upstream
=======
  CPPUNIT_TEST(testWrappedLength);
  CPPUNIT_TEST(testWrappedLengthLessThanParentWidth);
>>>>>>> Stashed changes
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testCreation();
  void testNestedPosition();
  void testNestedPositionX2();
<<<<<<< Updated upstream
=======
  void testWrappedLength();
  void testWrappedLengthLessThanParentWidth();
>>>>>>> Stashed changes

  private:
  TestBed* _testBed;
};

#endif
