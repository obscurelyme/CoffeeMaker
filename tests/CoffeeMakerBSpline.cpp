
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

void CoffeeMakerBSpline::testSetBSplineVector2DControlPoints() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  using Pt2 = CoffeeMaker::Math::Point2D;
  Scope<CoffeeMaker::BSpline> bSpline = CreateScope<CoffeeMaker::BSpline>();
  std::vector<Vec2> givenControlPoints{Vec2{0, 0}, Vec2{1, 1}, Vec2{2, 2}, Vec2{3, 3}};
  std::vector<Pt2> controlPoints;

  bSpline->SetControlPoints(givenControlPoints);
  controlPoints = bSpline->GetControlPoints();

  for (size_t i = 0; i < givenControlPoints.size(); i++) {
    CPPUNIT_ASSERT_EQUAL(givenControlPoints[i].x, controlPoints[i].x);
    CPPUNIT_ASSERT_EQUAL(givenControlPoints[i].y, controlPoints[i].y);
  }
}

void CoffeeMakerBSpline::testSetBSplinePoint2DControlPoints() {
  using Pt2 = CoffeeMaker::Math::Point2D;
  Scope<CoffeeMaker::BSpline> bSpline = CreateScope<CoffeeMaker::BSpline>();
  std::vector<Pt2> givenControlPoints{Pt2{.x = 0, .y = 0}, Pt2{.x = 1, .y = 1}, Pt2{.x = 2, .y = 2},
                                      Pt2{.x = 3, .y = 3}};
  std::vector<Pt2> controlPoints;

  bSpline->SetControlPoints(givenControlPoints);
  controlPoints = bSpline->GetControlPoints();

  for (size_t i = 0; i < givenControlPoints.size(); i++) {
    CPPUNIT_ASSERT_EQUAL(givenControlPoints[i].x, controlPoints[i].x);
    CPPUNIT_ASSERT_EQUAL(givenControlPoints[i].y, controlPoints[i].y);
  }
}

void CoffeeMakerBSpline::testSetBSplinePoint2DAtKnot() {
  using Pt2 = CoffeeMaker::Math::Point2D;
  Scope<CoffeeMaker::BSpline> bSpline = CreateScope<CoffeeMaker::BSpline>(5);
  std::vector<Pt2> givenControlPoints{Pt2{.x = 1, .y = 1}, Pt2{.x = 1.25, .y = 1.25}, Pt2{.x = 1.5, .y = 1.5},
                                      Pt2{.x = 1.75, .y = 1.75}, Pt2{.x = 2, .y = 2}};
  bSpline->SetControlPoints(givenControlPoints);

  CPPUNIT_ASSERT_EQUAL(1.5f, bSpline->Point2DAtKnot(0.5).x);
  CPPUNIT_ASSERT_EQUAL(1.5f, bSpline->Point2DAtKnot(0.5).y);

  CPPUNIT_ASSERT_EQUAL(1.0f, bSpline->Point2DAtKnot(0.0).x);
  CPPUNIT_ASSERT_EQUAL(1.0f, bSpline->Point2DAtKnot(0.0).y);

  CPPUNIT_ASSERT_EQUAL(2.0f, bSpline->Point2DAtKnot(1.0).x);
  CPPUNIT_ASSERT_EQUAL(2.0f, bSpline->Point2DAtKnot(1.0).y);

  CPPUNIT_ASSERT_EQUAL_MESSAGE("With domains exceeding 1.0", 2.0f, bSpline->Point2DAtKnot(1.5).x);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("With domains exceeding 1.0", 2.0f, bSpline->Point2DAtKnot(1.5).y);

  CPPUNIT_ASSERT_EQUAL_MESSAGE("With negative domains", 1.0f, bSpline->Point2DAtKnot(-1.0).x);
  CPPUNIT_ASSERT_EQUAL_MESSAGE("With negative domains", 1.0f, bSpline->Point2DAtKnot(-1.0).y);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerBSpline);
