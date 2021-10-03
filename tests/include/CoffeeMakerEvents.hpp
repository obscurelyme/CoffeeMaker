
#ifndef _coffeemaker_coffeemakerevents_hpp
#define _coffeemaker_coffeemakerevents_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoffeeMakerEvents : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerEvents);
  CPPUNIT_TEST(testEmitEvents);
  CPPUNIT_TEST(testRemoveEvents);
  CPPUNIT_TEST(testFunctionCreation);
  CPPUNIT_TEST(testFunctionComparison);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();

  void testEmitEvents();
  void testRemoveEvents();

  void testFunctionCreation();
  void testFunctionComparison();
};

#endif
