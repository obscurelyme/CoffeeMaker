
#ifndef _coffeemaker_coffeemakercomponent_hpp
#define _coffeemaker_coffeemakercomponent_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class CoffeeMakerComponent : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(CoffeeMakerComponent);
  CPPUNIT_TEST(testComponentCreation);
  CPPUNIT_TEST_SUITE_END();

  public:
    void setUp();
    void tearDown();

    void testComponentCreation();
};

#endif
