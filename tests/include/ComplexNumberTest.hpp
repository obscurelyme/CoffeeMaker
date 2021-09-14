#ifndef _coffeemaker_complexnumbertest_hpp
#define _coffeemaker_complexnumbertest_hpp

#include "Complex.hpp"
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class ComplexNumberTest : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(ComplexNumberTest);
  CPPUNIT_TEST(testEquality);
  CPPUNIT_TEST(testAddition);
  CPPUNIT_TEST_SUITE_END();

  private:
    Complex *_complex1, *_complex2, *_complex3;

  public:
    // static CppUnit::Test * suite();
    void setUp();
    void tearDown();

    // NOTE: write tests here...
    void testEquality();
    void testAddition();
};

#endif
