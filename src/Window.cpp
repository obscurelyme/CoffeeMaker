#include "Window.hpp"

using namespace CoffeeMaker;

std::string ScreenDPI::toString()
{
  return fmt::format("Diagonal {}, Horizontal {}, Vertical {}", diagonal, horizontal, vertical);
}

SDL_Window *Window::_window = nullptr;

Window::Window(std::string title, int width, int height)
{
  int windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
  _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
  _dpi = DotsPerInch();
  _dpiScale = _dpi.diagonal / ScreenDPI::BASE_DPI;
}

Window::~Window()
{
  if (_window != nullptr)
  {
    SDL_DestroyWindow(_window);
    _window = nullptr;
  }
}

SDL_Window *const Window::Instance()
{
  return _window;
}

void Window::Destroy()
{
  this->~Window();
}

int Window::DisplayCount()
{
  return SDL_GetNumVideoDisplays();
}

ScreenDPI Window::DotsPerInch()
{
  ScreenDPI dpi;
  SDL_GetDisplayDPI(SDL_GetWindowDisplayIndex(_window), &(dpi.diagonal), &(dpi.horizontal), &(dpi.vertical));
  return dpi;
}

float Window::DPIScale()
{
  return _dpiScale;
}

SDL_Surface *Window::Surface()
{
  return SDL_GetWindowSurface(_window);
}