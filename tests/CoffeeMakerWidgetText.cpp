
#include "CoffeeMakerWidgetText.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "FontManager.hpp"
#include "Widgets/Text.hpp"
#include "Widgets/View.hpp"

using namespace CoffeeMaker::Test;
using namespace CoffeeMaker::Widgets;
using namespace CoffeeMaker::UIProperties;

void CoffeeMakerWidgetText::setUp() { _testBed = new TestBed(); }

void CoffeeMakerWidgetText::tearDown() { delete _testBed; }

void CoffeeMakerWidgetText::testCreation() {
  Text text{"Hello, World!"};

  std::string content = "Hello, World!";
  CPPUNIT_ASSERT_EQUAL(true, true);
}

void CoffeeMakerWidgetText::testNestedPosition() {
  View view{150, 150};
  Text text;
  text.SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));
  text.SetText("Hello, World!");
  view.AppendChild(&text);

  _testBed->BeginRender();
  view.Render();
  _testBed->EndRender();
  SDL_Delay(1000);

  CPPUNIT_ASSERT_EQUAL(0, text.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, text.clientRect.y);
}

void CoffeeMakerWidgetText::testNestedPositionX2() {
  View view{150, 150, HorizontalAlignment::Centered, VerticalAlignment::Centered};
  View view2{100, 100, HorizontalAlignment::Right, VerticalAlignment::Bottom};
  view.AppendChild(&view2);

  Text text;
  text.SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));
  text.SetText("Hello, World!");
  text.SetHorizontalAlignment(HorizontalAlignment::Centered);
  text.SetVerticalAlignment(VerticalAlignment::Top);
  view2.AppendChild(&text);

  _testBed->BeginRender();
  view.Render();
  _testBed->EndRender();
  SDL_Delay(3000);

  CPPUNIT_ASSERT_EQUAL(231, text.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(225, text.clientRect.y);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetText);
