
#ifndef _coffeemaker_coffeemakerutilities_hpp
#define _coffeemaker_coffeemakerutilities_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoffeeMakerUtilities : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoffeeMakerUtilities);
  CPPUNIT_TEST(testBaseDirectory);
  CPPUNIT_TEST(testAssetDirectory);
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testBaseDirectory();
  void testAssetDirectory();
};

#endif
