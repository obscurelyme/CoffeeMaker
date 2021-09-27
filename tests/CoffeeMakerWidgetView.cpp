
#include "CoffeeMakerWidgetView.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Widgets/View.hpp"

using namespace CoffeeMaker::UIProperties;

void CoffeeMakerWidgetView::setUp() { _testBed = new CoffeeMaker::Test::TestBed(); }

void CoffeeMakerWidgetView::tearDown() { delete _testBed; }

void CoffeeMakerWidgetView::testDefaultViewport() {
  CoffeeMaker::Widgets::View view(100, 150);

  CPPUNIT_ASSERT_EQUAL(0, view.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, view.clientRect.y);
  CPPUNIT_ASSERT_EQUAL(100, view.clientRect.w);
  CPPUNIT_ASSERT_EQUAL(150, view.clientRect.h);

  CPPUNIT_ASSERT_EQUAL(0, view.viewport.x);
  CPPUNIT_ASSERT_EQUAL(0, view.viewport.y);
  CPPUNIT_ASSERT_EQUAL(500, view.viewport.w);
  CPPUNIT_ASSERT_EQUAL(500, view.viewport.h);
}

void CoffeeMakerWidgetView::testCentered() {
  CoffeeMaker::Widgets::View view(100, 150, HorizontalAlignment::Centered, VerticalAlignment::Centered);

  CPPUNIT_ASSERT_EQUAL(200, view.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(175, view.clientRect.y);
  CPPUNIT_ASSERT_EQUAL(100, view.clientRect.w);
  CPPUNIT_ASSERT_EQUAL(150, view.clientRect.h);
}

void CoffeeMakerWidgetView::testRightBottomAligned() {
  CoffeeMaker::Widgets::View view(100, 150, HorizontalAlignment::Right, VerticalAlignment::Bottom);

  CPPUNIT_ASSERT_EQUAL(400, view.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(350, view.clientRect.y);
  CPPUNIT_ASSERT_EQUAL(100, view.clientRect.w);
  CPPUNIT_ASSERT_EQUAL(150, view.clientRect.h);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetView);
