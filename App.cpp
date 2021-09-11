#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <spdlog/spdlog.h>
#include <filesystem>
#include "Window.hpp"

void write(std::string text, int x, int y);
void render();
void input();

bool quit = false;
SDL_Renderer *renderer = nullptr;
TTF_Font *font = nullptr;
SDL_Event event;
SDL_Rect textBoard;

int main(int argc, char **argv)
{
  spdlog::set_level(spdlog::level::debug);

  std::string executableDirectory = std::filesystem::weakly_canonical(std::filesystem::path(argv[0])).parent_path().string();
  std::string relativeFontFile = "/assets/fonts/Roboto/Roboto-Regular.ttf";
  std::string fontFilePath = executableDirectory.append(relativeFontFile);

  if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    spdlog::critical("Could not initialize SDL2!");
    exit(1);
  }

  if (TTF_Init() == -1)
  {
    spdlog::critical("Could not initialize SDL-TTF!");
    exit(1);
  }
  else
  {
    spdlog::debug("SDL-TTF successfully initialized!");
    font = TTF_OpenFont(fontFilePath.c_str(), 16);
    if (font == nullptr)
    {
      spdlog::critical("Could not load font from given filePath: {}", fontFilePath);
    }
    else
    {
      spdlog::debug("Successfully opened font at filepath {}", fontFilePath);
    }
  }

  CoffeeMaker::Window win("Hello, SDL!", 800, 600);
  renderer = SDL_CreateRenderer(win.instance(), -1, 0);

  while (!quit)
  {
    input();
    render();
  }

  SDL_DestroyRenderer(renderer);
  win.Destroy();
  TTF_CloseFont(font);
  SDL_Quit();

  return 0;
}

void render()
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  // Do all rendering here...
  write("Hello, World!", 20, 20);

  SDL_RenderPresent(renderer);
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

void write(std::string text, int x, int y)
{
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Color color{
      .r = 0,
      .g = 0,
      .b = 0,
      .a = 255};
  surface = TTF_RenderText_Blended(font, text.c_str(), color);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  textBoard.w = surface->w;
  textBoard.h = surface->h;
  textBoard.x = 0; // x - textBoard.w;
  textBoard.y = 0; // y - textBoard.h;
  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL, &textBoard);
  SDL_DestroyTexture(texture);
}
