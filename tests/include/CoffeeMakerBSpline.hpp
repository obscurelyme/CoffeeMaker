
#ifndef _coffeemaker_coffeemakerbspline_hpp
#define _coffeemaker_coffeemakerbspline_hpp

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Spline.hpp"

class CoffeeMakerBSpline : public CppUnit::TestFixture {
  CPPUNIT_TEST_SUITE(CoffeeMakerBSpline);
  // TODO append your unit tests here
  CPPUNIT_TEST(testCreateBSpline);
  CPPUNIT_TEST_SUITE_END();

  public:
  friend CoffeeMaker::BSpline;

  void setUp();
  void tearDown();

  void testCreateBSpline();
};

#endif
