
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerTextureTest.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"
#include "Logger.hpp"
#include "Color.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void CoffeeMakerTextureTest::setUp()
{
  _testBed = new CoffeeMaker::Test::TestBed();
}

void CoffeeMakerTextureTest::tearDown()
{
  delete _testBed;
}

void CoffeeMakerTextureTest::testCreateTexture()
{
  CoffeeMaker::Texture texture;

  CPPUNIT_ASSERT_EQUAL(texture.Height(), 0);
  CPPUNIT_ASSERT_EQUAL(texture.Width(), 0);
}

void CoffeeMakerTextureTest::testLoadTexture()
{
  CoffeeMaker::Texture texture;
  texture.LoadFromFile("test.png");

  CPPUNIT_ASSERT_EQUAL(texture.Height(), 150);
  CPPUNIT_ASSERT_EQUAL(texture.Width(), 150);
}

void CoffeeMakerTextureTest::testRender()
{
  CoffeeMaker::Texture texture("test.png");
  _testBed->BeginRender();

  texture.Render(50, 50);

  _testBed->EndRender();
  SDL_Delay(1000); // just so you can see the image

  CPPUNIT_ASSERT_EQUAL(true, true);
}

void CoffeeMakerTextureTest::testCreateTextureColor()
{
  CoffeeMaker::Texture texture(CoffeeMaker::Color(255, 0, 0, 255));
  texture.SetHeight(50);
  texture.SetWidth(100);

  _testBed->BeginRender();

  texture.Render(50, 50);

  _testBed->EndRender();
  SDL_Delay(1000); // just so you can see the image

  CPPUNIT_ASSERT_EQUAL(true, true);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerTextureTest);
