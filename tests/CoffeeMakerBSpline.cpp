
#include "CoffeeMakerBSpline.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Utilities.hpp"

void CoffeeMakerBSpline::setUp() {
  // TODO: Implement set up logic...
}

void CoffeeMakerBSpline::tearDown() {
  // TODO: Implement tear down logic...
}

void CoffeeMakerBSpline::testCreateBSpline() {
  using Pt2 = CoffeeMaker::Math::Point2D;
  Scope<CoffeeMaker::BSpline> bspline = CreateScope<CoffeeMaker::BSpline>();
  size_t expectedSize = 4;
  float expectedZeroValue = 0.0f;

  std::vector<Pt2> points = bspline->GetControlPoints();

  CPPUNIT_ASSERT_EQUAL(expectedSize, points.size());

  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[0].x);
  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[0].y);

  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[1].x);
  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[1].y);

  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[2].x);
  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[2].y);

  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[3].x);
  CPPUNIT_ASSERT_EQUAL(expectedZeroValue, points[3].y);
}

void CoffeeMakerBSpline::testSetBSplineTinysplineRealControlPoints() {
  Scope<CoffeeMaker::BSpline> bSpline = CreateScope<CoffeeMaker::BSpline>();
  std::vector<tinyspline::real> givenControlPoints{0, 0, 1, 1, 2, 2, 3, 3};
  std::vector<CoffeeMaker::Math::Point2D> controlPoints;

  bSpline->SetControlPoints(givenControlPoints);
  controlPoints = bSpline->GetControlPoints();

  for (size_t i = 0; i < givenControlPoints.size() / 2; i++) {
    CPPUNIT_ASSERT_EQUAL(static_cast<float>(givenControlPoints[i * 2]), controlPoints[i].x);
    CPPUNIT_ASSERT_EQUAL(static_cast<float>(givenControlPoints[i * 2 + 1]), controlPoints[i].y);
  }
}

void CoffeeMakerBSpline::testSetBSplineVector2DControlPoints() {}
void CoffeeMakerBSpline::testSetBSplinePoint2DControlPoints() {}
void CoffeeMakerBSpline::testSetBSplineTinysplineRealControlPointAt() {}
void CoffeeMakerBSpline::testSetBSplineVector2DControlPointAt() {}
void CoffeeMakerBSpline::testSetBSplinePoint2DControlPointAt() {}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerBSpline);
