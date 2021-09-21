#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <filesystem>
#include "FontManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "TextView.hpp"
#include "Widgets/Button.hpp"
#include "Widgets/Image.hpp"
#include "Utilities.hpp"
#include "Primitives/Rect.hpp"
#include "Primitives/Line.hpp"
#include "Logger.hpp"
#include "Color.hpp"
#include "Cursor.hpp"
#include "Widgets/View.hpp"

#include <chrono>

void input();

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

  CoffeeMaker::Cursor cursor("cursor.png");
  CoffeeMaker::FontManager fontManager;
  fontManager.loadFont("Roboto/Roboto-Regular");

  CoffeeMaker::BasicWindow win("Hello, SDL!", 800, 600);
  CoffeeMaker::Renderer renderer;
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<float> elapsedSeconds = end - start;
  CoffeeMaker::Logger::Info(fmt::format("Initialization time took: {}", elapsedSeconds.count()));

  // NOTE: Construct the UI
  CoffeeMaker::Widgets::View view(800, 600);
  CoffeeMaker::Widgets::View view2(400, 300, CoffeeMaker::Widgets::ViewXProps::RIGHT_ALIGNED, CoffeeMaker::Widgets::ViewYProps::BOTTOM_ALIGNED);

  CoffeeMaker::TextView text{"Hello, World!"};
  text.color = CoffeeMaker::Color(255, 255, 255, 255);
  text.SetFont(fontManager.useFont("Roboto/Roboto-Regular"));
  text.SetTextContentTexture();

  CoffeeMaker::Button button;
  CoffeeMaker::Button button2;
  button.clientRect.y = 100;
  button.clientRect.x = 200;
  button.AppendChild(&text);

  view.AppendChild(&button);
  view2.AppendChild(&button2);

  CM_LOGGER_INFO("Display count: {}", win.DisplayCount());
  CM_LOGGER_INFO("Current Window DPI {}", win.GetScreenDPI().toString());

  while (!quit)
  {
    // get input
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }
      button.OnEvent(&event);
    }

    // run logic

    // render
    renderer.BeginRender();

    view.Render();
    view2.Render();

    renderer.EndRender();

    // Cap framerate
    SDL_Delay(16);
  }

  renderer.Destroy();
  SDL_Quit();

  CM_LOGGER_DESTROY();

  return 0;
}

void input()
{
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_QUIT)
    {
      quit = true;
    }
  }
}
