
#ifndef _coffeemaker_coffeemakercoroutine_hpp
#define _coffeemaker_coffeemakercoroutine_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoffeeMakerCoroutine : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerCoroutine);
  CPPUNIT_TEST(testCoroutineCreation);
  CPPUNIT_TEST(testCoroutineAwaiter);
  CPPUNIT_TEST(testCoroutineReadFileAwaiter);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();
  void testCoroutineCreation();
  void testCoroutineAwaiter();
  void testCoroutineReadFileAwaiter();
};

#endif
