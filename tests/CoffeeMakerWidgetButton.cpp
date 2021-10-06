
#include "CoffeeMakerWidgetButton.hpp"

#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include <memory>

#include "FontManager.hpp"
#include "TestBed.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Text.hpp"

void CoffeeMakerWidgetButton::setUp() { _testBed = new CoffeeMaker::Test::TestBed(); }

void CoffeeMakerWidgetButton::tearDown() { delete _testBed; }

void CoffeeMakerWidgetButton::testButtonCreation() {
  CoffeeMaker::Button button;

  CPPUNIT_ASSERT_EQUAL(0, button.top);
  CPPUNIT_ASSERT_EQUAL(0, button.left);
  CPPUNIT_ASSERT_EQUAL(0, button._texture.Height());
  CPPUNIT_ASSERT_EQUAL(0, button._texture.Width());
}

void CoffeeMakerWidgetButton::testButtonCreatesTexture() {
  CoffeeMaker::Button button;

  CPPUNIT_ASSERT_EQUAL(0, button.left);
  CPPUNIT_ASSERT_EQUAL(0, button.top);
  CPPUNIT_ASSERT_EQUAL(150, button.width);
  CPPUNIT_ASSERT_EQUAL(50, button.height);
}

void CoffeeMakerWidgetButton::testButtonRender() {
  CoffeeMaker::Button button;
  button.top = 50;
  button.left = 50;

  _testBed->BeginRender();

  CPPUNIT_ASSERT_NO_THROW(button.Render());

  _testBed->EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testButtonOnMousemotionEvent() {
  CoffeeMaker::Button button;
  button.top = 50;
  button.left = 50;

  // Initial render the button
  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);

  // Mouseover the button
  button.OnMouseover();
  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);

  // Mouseleave the button
  button.OnMouseleave();
  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testSetButtonBackgroundColor() {
  CoffeeMaker::Button button;
  std::shared_ptr<CoffeeMaker::Widgets::Text> text(new CoffeeMaker::Widgets::Text());

  button.SetTexture("test-button-background.png");
  text->SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));
  text->SetText("Click Me");
  text->SetColor(CoffeeMaker::Color(255, 255, 255, 255));
  text->SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment::Centered);
  text->SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment::Centered);
  button.AppendChild(text);

  _testBed->BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  _testBed->EndRender();
  SDL_Delay(1000);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetButton);
