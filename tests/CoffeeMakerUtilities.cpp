
#include <cppunit/TestAssert.h>
#include <cppunit/extensions/HelperMacros.h>

#include "CoffeeMakerUtilities.hpp"

#include <SDL2/SDL.h>
#include "Utilities.hpp"

void CoffeeMakerUtilities::setUp()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  CoffeeMaker::Utilities::Init("/");
}

void CoffeeMakerUtilities::tearDown()
{
  SDL_Quit();
}

void CoffeeMakerUtilities::testBaseDirectory()
{
  std::string path = CoffeeMaker::Utilities::BaseDirectory();
  std::string expectedPath = "/";
  CPPUNIT_ASSERT_EQUAL(expectedPath, path);
}

void CoffeeMakerUtilities::testAssetDirectory()
{
  std::string path = CoffeeMaker::Utilities::AssetsDirectory();
  std::string expectedPath = "/assets";
  CPPUNIT_ASSERT_EQUAL(expectedPath, path);
}

CPPUNIT_TEST_SUITE_REGISTRATION(CoffeeMakerUtilities);
