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

#include <chrono>

void input();

bool quit = false;
SDL_Event event;

int main(int, char **)
{
  // Start clock
  auto start = std::chrono::steady_clock::now();

  CoffeeMaker::Texture::SetTextureDirectory();
  CoffeeMaker::Logger::Init();

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    CoffeeMaker::Logger::Critical("Could not initialize SDL2!");
    exit(1);
  }

  if (IMG_Init(IMG_INIT_PNG) == 0)
  {
    CoffeeMaker::Logger::Critical("Could not initialize SDL2 Images");
    exit(1);
  }

  CoffeeMaker::Cursor cursor("cursor.png");
  CoffeeMaker::FontManager fontManager;
  fontManager.loadFont("Roboto/Roboto-Regular");

  CoffeeMaker::BasicWindow win("Hello, SDL!", 800, 600);
  CoffeeMaker::Renderer renderer;
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<float> elapsedSeconds = end - start;
  CoffeeMaker::Logger::Info(fmt::format("Initialization time took: {}", elapsedSeconds.count()));

  CoffeeMaker::TextView text{"Hello, World!"};
  text.color = CoffeeMaker::Color(255, 255, 255, 255);
  text.SetFont(fontManager.useFont("Roboto/Roboto-Regular"));
  text.SetTextContentTexture();

  CoffeeMaker::Button button;
  button.clientRect.y = 100;
  button.clientRect.x = 200;
  CoffeeMaker::Texture texture("test.png");
  CoffeeMaker::Widgets::Image img("loaded.png");
  img.LoadImage();
  CoffeeMaker::Shapes::Rect rect(100, 100);
  CoffeeMaker::Shapes::Line line(100, 600 / 2, 800 / 2, 0);

  button.AppendChild(&text);

  CoffeeMaker::Logger::Info(fmt::format("Display count: {}", win.DisplayCount()));
  CoffeeMaker::Logger::Info(fmt::format("Current Window DPI {}", win.GetScreenDPI().toString()));

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
    // line.Rotate(5);

    // render
    renderer.BeginRender();

    button.Render();
    // img.Render();
    // text.Render();
    // rect.Render();
    // texture.Render(0, 0);
    // line.Render();
    renderer.EndRender();

    // Cap framerate
    SDL_Delay(16);
  }

  renderer.Destroy();
  SDL_Quit();

  CoffeeMaker::Logger::Destroy();

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
