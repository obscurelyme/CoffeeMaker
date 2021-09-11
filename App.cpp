#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>
#include <filesystem>
#include "FontManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"
#include "TextView.hpp"

void input();

bool quit = false;
SDL_Event event;

int main(int argc, char **argv)
{
  spdlog::set_level(spdlog::level::debug);

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    spdlog::critical("Could not initialize SDL2!");
    exit(1);
  }

  CoffeeMaker::FontManager fontManager(argv[0]);
  fontManager.loadFont("Roboto/Roboto-Regular");

  CoffeeMaker::Window win("Hello, SDL!", 800, 600);
  CoffeeMaker::Renderer renderer(&win);

  CoffeeMaker::TextView text{"Hello, World!"};
  text.AssignToRenderer(renderer.Instance());
  text.SetFont(fontManager.useFont("Roboto/Roboto-Regular"));

  spdlog::info("Display count: {}", win.DisplayCount());
  spdlog::info("Current Window DPI {}", win.DotsPerInch().toString());

  while (!quit)
  {
    input();
    renderer.BeginRender();
    text.Render();
    renderer.EndRender();
  }

  renderer.Destroy();
  win.Destroy();
  SDL_Quit();

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
