
#include "CoffeeMakerWidgetButton.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

#include "FontManager.hpp"
#include "TestBed.hpp"
#include "Utilities.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Properties.hpp"
#include "Widgets/Text.hpp"

using namespace CoffeeMaker::UIProperties;
using namespace CoffeeMaker;
using namespace CoffeeMaker::Widgets;

void CoffeeMakerWidgetButton::setUp() { _testBed = new CoffeeMaker::Test::TestBed(); }

void CoffeeMakerWidgetButton::tearDown() { delete _testBed; }

void CoffeeMakerWidgetButton::testButtonCreation() {
  Button button;

  CPPUNIT_ASSERT_EQUAL(0, button.clientRect.y);
  CPPUNIT_ASSERT_EQUAL(0, button.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(50, button.clientRect.h);
  CPPUNIT_ASSERT_EQUAL(100, button.clientRect.w);
}

void CoffeeMakerWidgetButton::testButtonCreatesTexture() {
  Button button{"test-button-background.png", "test-button-background-hovered.png"};

  CPPUNIT_ASSERT_EQUAL(0, button.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, button.clientRect.y);
  // NOTE: 150 matches the width of the image
  CPPUNIT_ASSERT_EQUAL(150, button.clientRect.w);
  // NOTE: 50 matches the height of the image
  CPPUNIT_ASSERT_EQUAL(50, button.clientRect.h);
}

void CoffeeMakerWidgetButton::testButtonDynamicPosition() {
  Button button{"test-button-background.png", "test-button-background-hovered.png"};
  button.SetVerticalAlignment(VerticalAlignment::Centered);
  button.SetHorizontalAlignment(HorizontalAlignment::Centered);

  CPPUNIT_ASSERT_EQUAL(175, button.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(225, button.clientRect.y);
}

void CoffeeMakerWidgetButton::testButtonRenderTexture() {
  Button button{"test-button-background.png", "test-button-background-hovered.png"};
  button.SetVerticalAlignment(VerticalAlignment::Centered);
  button.SetHorizontalAlignment(HorizontalAlignment::Centered);

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);

  button.OnMouseover();

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);

  button.OnMouseleave();

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testButtonRenderTextureAndText() {
  Button button{"test-button-background.png", "test-button-background-hovered.png"};
  Ref<Text> text{new Text("Click Me!")};
  text->SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));

  button.AppendChild(text);
  text->SetHorizontalAlignment(HorizontalAlignment::Centered);
  text->SetVerticalAlignment(VerticalAlignment::Centered);

  button.SetHorizontalAlignment(HorizontalAlignment::Centered);
  button.SetVerticalAlignment(VerticalAlignment::Centered);

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testButtonRenderColor() {
  Button button{Color(255, 0, 255, 255), Color(0, 255, 0, 255), 150, 50};

  CPPUNIT_ASSERT_EQUAL(0, button.clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, button.clientRect.y);
  CPPUNIT_ASSERT_EQUAL(50, button.clientRect.h);
  CPPUNIT_ASSERT_EQUAL(150, button.clientRect.w);

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);

  button.OnMouseover();

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testTextAppendedToDefaultButton() {
  Button button;
  Ref<Text> text(new Text("Hello, World!"));
  text->SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));

  button.AppendChild(text);

  CPPUNIT_ASSERT_EQUAL(88, text->clientRect.w);
  CPPUNIT_ASSERT_EQUAL(19, text->clientRect.h);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetButton);
