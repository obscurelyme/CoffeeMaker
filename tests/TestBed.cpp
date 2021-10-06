#include "TestBed.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cppunit/TestAssert.h>

#include "FontManager.hpp"
#include "Logger.hpp"
#include "Texture.hpp"
#include "Utilities.hpp"

using namespace CoffeeMaker::Test;

TestBed::TestBed() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    CPPUNIT_FAIL("SDL was not successfully initialized");
  }
  if (IMG_Init(IMG_INIT_PNG) != 2) {
    CPPUNIT_FAIL("SDL_Image was not successfully initialized");
  }
  CoffeeMaker::Utilities::Init(SDL_GetBasePath());
  CoffeeMaker::Texture::SetTextureDirectory();
  CoffeeMaker::Logger::Init();
  CoffeeMaker::FontManager::Init();
  CoffeeMaker::FontManager::LoadFont("Roboto/Roboto-Regular");
  _window = new CoffeeMaker::BasicWindow("test window", 500, 500);
  _renderer = new CoffeeMaker::Renderer();

  ((CoffeeMaker::BasicWindow*)_window)->ShowWindow();
}

TestBed::~TestBed() {
  delete _renderer;
  delete _window;
  IMG_Quit();
  SDL_Quit();
}

void TestBed::Reset() {}

void TestBed::ClearScreen() {
  _renderer->BeginRender();
  _renderer->EndRender();
}

void TestBed::BeginRender() { _renderer->BeginRender(); }

void TestBed::EndRender() { _renderer->EndRender(); }
