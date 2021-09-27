
#include "CoffeeMakerWidgetText.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

using namespace CoffeeMaker::Test;
using namespace CoffeeMaker::Widgets;

void CoffeeMakerWidgetText::setUp() { _testBed = new TestBed(); }

void CoffeeMakerWidgetText::tearDown() { delete _testBed; }

void CoffeeMakerWidgetText::testCreation() {
  Text text{"Hello, World!"};

  std::string content = "Hello, World!";
  CPPUNIT_ASSERT_EQUAL(true, true);
}

void CoffeeMakerWidgetText::testNestedPosition() {
  View view{150, 150};
  Text text{"Hello, World!"};
  text.SetFont((TTF_Font*)123);  // Dummy font
  view.AppendChild(&text);

  _testBed->BeginRender();
  view.Render();
  _testBed->EndRender();

  CPPUNIT_ASSERT_EQUAL(0, text.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, text.clientRect.y);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetText);
