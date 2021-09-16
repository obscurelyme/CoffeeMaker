
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerTextureTest.hpp"
#include "Widgets/Button.hpp"
#include "Utilities.hpp"
#include "Logger.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void CoffeeMakerTextureTest::setUp()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    CPPUNIT_FAIL("SDL was not successfully initialized");
  }
  if (IMG_Init(IMG_INIT_PNG) != 2)
  {
    CPPUNIT_FAIL("SDL_Image was not successfully initialized");
  }
  CoffeeMaker::Utilities::Init(SDL_GetBasePath());
  CoffeeMaker::Texture::SetTextureDirectory();
  CoffeeMaker::Logger::Init();
  _window = new CoffeeMaker::BasicWindow("test window", 500, 500);
  _renderer = new CoffeeMaker::Renderer();
}

void CoffeeMakerTextureTest::tearDown()
{
  delete _renderer;
  delete _window;
  IMG_Quit();
  SDL_Quit();
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
  _renderer->BeginRender();

  texture.Render(50, 50);

  _renderer->EndRender();
  SDL_Delay(1000); // just so you can see the image

  CPPUNIT_ASSERT_EQUAL(true, true);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerTextureTest);
