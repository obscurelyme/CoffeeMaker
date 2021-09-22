#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <filesystem>
#include "FontManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "Utilities.hpp"
#include "Logger.hpp"
#include "Cursor.hpp"
#include "FPS.hpp"
#include "TextView.hpp"

#include "Game/Entity.hpp"
#include "Game/Tiles.hpp"

#include <chrono>

bool quit = false;
SDL_Event event;

int main(int, char **)
{
  // Start clock
  auto start = std::chrono::steady_clock::now();
  CM_LOGGER_INIT();

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    CM_LOGGER_CRITICAL("Could not initialize SDL2!");
    exit(1);
  }

  if (IMG_Init(IMG_INIT_PNG) == 0)
  {
    CM_LOGGER_CRITICAL("Could not initialize SDL2 Images");
    exit(1);
  }

  CoffeeMaker::Utilities::Init(SDL_GetBasePath());
  CoffeeMaker::Texture::SetTextureDirectory();

  CoffeeMaker::BasicWindow win("Hello, SDL!", 800, 600);
  CoffeeMaker::Renderer renderer;

  CoffeeMaker::Cursor cursor("cursor.png");
  CoffeeMaker::FontManager::Init();
  CoffeeMaker::FontManager::LoadFont("Roboto/Roboto-Regular");
  CoffeeMaker::FontManager::LoadFont("Roboto/Roboto-Black");

  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<float> elapsedSeconds = end - start;

  CoffeeMaker::FPS fpsCounter;
  // CoffeeMaker::TextView text("00");
  // text.SetFont(CoffeeMaker::FontManager::UseFont("Roboto/Roboto-Regular"));
  // text.SetTextContentTexture();

  CM_LOGGER_INFO("Initialization time took: {}", elapsedSeconds.count());
  CM_LOGGER_INFO("Display count: {}", win.DisplayCount());
  CM_LOGGER_INFO("Current Window DPI {}", win.GetScreenDPI().toString());

  Enemy enemy;
  Tiles tiles("space.png", 800, 600);

  win.ShowWindow();

  while (!quit)
  {
    // get input
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    // run logic
    enemy.Update();
    fpsCounter.Update();

    // render
    renderer.BeginRender();

    tiles.Render();
    enemy.Render();
    fpsCounter.Render();

    renderer.EndRender();

    // Cap framerate
    SDL_Delay(16);
  }

  renderer.Destroy();
  SDL_Quit();
  CM_LOGGER_DESTROY();

  return 0;
}
