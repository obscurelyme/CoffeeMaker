
#ifndef _coffeemaker_coffeemakerdatetime_hpp
#define _coffeemaker_coffeemakerdatetime_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "DateTime.hpp"

class CoffeeMakerDateTime : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerDateTime);
  CPPUNIT_TEST(testDateTimeFormatTemplate);
  CPPUNIT_TEST_SUITE_END();

  public:
  void setUp();
  void tearDown();
  void testDateTimeFormatTemplate();
};

#endif
