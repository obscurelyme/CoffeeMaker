
#include "CoffeeMakerBSpline.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

void CoffeeMakerBSpline::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerBSpline::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerBSpline::testCreateBSpline() {
  using Pt2 = CoffeeMaker::Math::Point2D;
  CoffeeMaker::BSpline* bspline = new CoffeeMaker::BSpline();

  std::vector<Pt2> points = bspline->GetControlPoints();

  CPPUNIT_ASSERT_EQUAL(4UL, points.size());
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerBSpline);
