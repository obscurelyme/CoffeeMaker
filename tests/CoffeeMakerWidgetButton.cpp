
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerWidgetButton.hpp"
#include "Widgets/Button.hpp"
#include "TestBed.hpp"

void CoffeeMakerWidgetButton::setUp() {}

void CoffeeMakerWidgetButton::tearDown() {}

void CoffeeMakerWidgetButton::testButtonCreation()
{
  CoffeeMaker::Button button;

  CPPUNIT_ASSERT_EQUAL(0, button.top);
  CPPUNIT_ASSERT_EQUAL(0, button.left);
  CPPUNIT_ASSERT_EQUAL(0, button._texture.Height());
  CPPUNIT_ASSERT_EQUAL(0, button._texture.Width());
}

void CoffeeMakerWidgetButton::testButtonCreatesTexture()
{
  CoffeeMaker::Button button;

  CPPUNIT_ASSERT_EQUAL(0, button._clientRect.x);
  CPPUNIT_ASSERT_EQUAL(0, button._clientRect.y);
  CPPUNIT_ASSERT_EQUAL(0, button._clientRect.w);
  CPPUNIT_ASSERT_EQUAL(0, button._clientRect.h);
}

void CoffeeMakerWidgetButton::testButtonRender()
{
  CoffeeMaker::Test::TestBed testBed;

  CoffeeMaker::Button button;
  button.top = 50;
  button.left = 50;

  testBed.BeginRender();

  CPPUNIT_ASSERT_NO_THROW(button.Render());

  testBed.EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testButtonOnMousemotionEvent()
{
  CoffeeMaker::Test::TestBed testBed;

  CoffeeMaker::Button button;
  button.top = 50;
  button.left = 50;

  // Initial render the button
  testBed.BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  testBed.EndRender();
  SDL_Delay(1000);

  // Mouseover the button
  button.OnMouseover();
  testBed.BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  testBed.EndRender();
  SDL_Delay(1000);

  // Mouseleave the button
  button.OnMouseleave();
  testBed.BeginRender();
  CPPUNIT_ASSERT_NO_THROW(button.Render());
  testBed.EndRender();
  SDL_Delay(1000);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetButton);
