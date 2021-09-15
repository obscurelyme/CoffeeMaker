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

void input();

bool quit = false;
SDL_Event event;

int main(int, char **argv)
{
  CoffeeMaker::Utilities::EXECUTABLE_PATH = argv[0];
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

  CoffeeMaker::FontManager fontManager;
  fontManager.loadFont("Roboto/Roboto-Regular");

  CoffeeMaker::BasicWindow win("Hello, SDL!", 800, 600);
  CoffeeMaker::Renderer renderer;

  CoffeeMaker::TextView text{"Hello, World!"};
  text.SetFont(fontManager.useFont("Roboto/Roboto-Regular"));

  // CoffeeMaker::Button button;
  CoffeeMaker::Widgets::Image img("loaded.png");
  img.LoadImage();
  CoffeeMaker::Shapes::Rect rect(100, 100);
  CoffeeMaker::Shapes::Line line(100, 600 / 2, 800 / 2, 0);

  CoffeeMaker::Logger::Info(fmt::format("Display count: {}", win.DisplayCount()));
  CoffeeMaker::Logger::Info(fmt::format("Current Window DPI {}", win.GetScreenDPI().toString()));

  while (!quit)
  {
    // get input
    input();

    // run logic
    line.Rotate(5);

    // render
    renderer.BeginRender();
    // img.Render();
    // text.Render();
    // rect.Render();
    line.Render();
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
