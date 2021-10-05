
#include "CoffeeMakerWidgetText.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

#include "FontManager.hpp"
#include "Utilities.hpp"
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
  Ref<Text> text{new Text()};
  text->SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));
  text->SetText("Hello, World!");
  view.AppendChild(text);

  _testBed->BeginRender();
  view.Render();
  _testBed->EndRender();
  SDL_Delay(1000);

  CPPUNIT_ASSERT_EQUAL(0, text->clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, text->clientRect.y);
}

void CoffeeMakerWidgetText::testNestedPositionX2() {
  Ref<View> view{new View(150, 150, HorizontalAlignment::Centered, VerticalAlignment::Centered)};
  Ref<View> view2{new View(100, 100, HorizontalAlignment::Right, VerticalAlignment::Bottom)};
  view->AppendChild(view2);

  Ref<Text> text{new Text()};
  text->SetHorizontalAlignment(HorizontalAlignment::Centered);
  text->SetVerticalAlignment(VerticalAlignment::Top);
  text->SetText("Hello, World!");
  text->SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));

  CPPUNIT_ASSERT_EQUAL(206, text->clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, text->clientRect.y);

  view2->AppendChild(text);

  _testBed->BeginRender();
  view->Render();
  _testBed->EndRender();
  SDL_Delay(3000);

  CPPUNIT_ASSERT_EQUAL(231, text->clientRect.x);
  CPPUNIT_ASSERT_EQUAL(225, text->clientRect.y);
}

void CoffeeMakerWidgetText::testWrappedLengthLessThanParentWidth() {
  Ref<View> view(new View(400, 400));
  Ref<Text> text(new Text("lorem ipsum dolor sit amet, consectetur adip"));
  text->SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));

  view->AppendChild(text);

  CPPUNIT_ASSERT_EQUAL(313, text->clientRect.w);
}

void CoffeeMakerWidgetText::testWrappedLength() {
  Ref<View> view(new View(100, 100));
  Ref<Text> text(new Text("lorem ipsum dolor sit amet, consectetur adip"));
  text->SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));
  text->SetWrapLength(50);

  CPPUNIT_ASSERT_EQUAL(50, text->clientRect.w);

  view->AppendChild(text);
  text->SetWrapLength(0);

  CPPUNIT_ASSERT_EQUAL(100, text->clientRect.w);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetText);
