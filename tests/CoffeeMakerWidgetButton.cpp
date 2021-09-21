
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerWidgetButton.hpp"
#include "Widgets/Button.hpp"
#include "TestBed.hpp"

void CoffeeMakerWidgetButton::setUp()
{
  _testBed = new CoffeeMaker::Test::TestBed();
}

void CoffeeMakerWidgetButton::tearDown()
{
  delete _testBed;
}

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

  CPPUNIT_ASSERT_EQUAL(0, button.left);
  CPPUNIT_ASSERT_EQUAL(0, button.top);
  CPPUNIT_ASSERT_EQUAL(150, button.width);
  CPPUNIT_ASSERT_EQUAL(50, button.height);
}

void CoffeeMakerWidgetButton::testButtonRender()
{
  CoffeeMaker::Button button;
  button.top = 50;
  button.left = 50;

  _testBed->BeginRender();

  CPPUNIT_ASSERT_NO_THROW(button.Render());

  _testBed->EndRender();
  SDL_Delay(1000);
}

void CoffeeMakerWidgetButton::testButtonOnMousemotionEvent()
{
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

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerWidgetButton);
