#include "Window.hpp"

using namespace CoffeeMaker;

IWindow *GlobalWindow::_instance = nullptr;

GlobalWindow::GlobalWindow() {}

GlobalWindow::GlobalWindow(IWindow *win) {
  if (_instance == nullptr) {
    _instance = win;
  }
}

IWindow *GlobalWindow::Instance() { return _instance; }

void GlobalWindow::Set(IWindow *win) {
  if (_instance == nullptr) {
    _instance = win;
  }
}

void GlobalWindow::Unset() { _instance = nullptr; }

std::string ScreenDPI::toString() {
  return fmt::format("Diagonal {}, Horizontal {}, Vertical {}", diagonal, horizontal, vertical);
}

SDL_Window *BasicWindow::_window = nullptr;

BasicWindow::BasicWindow(std::string title, int width, int height) {
  int windowFlags = SDL_WINDOW_HIDDEN;
  _window =
      SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
  _screenDpi = SetScreenDPI();
  _dpiScale = _screenDpi.diagonal / ScreenDPI::BASE_DPI;
  GlobalWindow::Set(this);
}

BasicWindow::~BasicWindow() {
  if (_window != nullptr) {
    if (GlobalWindow::Instance() == this) {
      GlobalWindow::Unset();
    }
    SDL_DestroyWindow(_window);
    _window = nullptr;
  }
}

int BasicWindow::DisplayCount() const { return SDL_GetNumVideoDisplays(); }

ScreenDPI BasicWindow::SetScreenDPI() {
  ScreenDPI dpi;
  SDL_GetDisplayDPI(SDL_GetWindowDisplayIndex(_window), &(dpi.diagonal), &(dpi.horizontal), &(dpi.vertical));
  return dpi;
}

ScreenDPI BasicWindow::GetScreenDPI() const { return _screenDpi; }

float BasicWindow::DPIScale() const { return _dpiScale; }

SDL_DisplayMode BasicWindow::DisplayMode() const {
  SDL_DisplayMode displayMode;
  SDL_GetWindowDisplayMode(_window, &displayMode);
  return displayMode;
}

std::string BasicWindow::DisplayName() const { return SDL_GetDisplayName(SDL_GetWindowDisplayIndex(_window)); }

Uint32 BasicWindow::PixelFormat() const { return SDL_GetWindowPixelFormat(_window); }

std::string BasicWindow::PixelFormatName() const { return SDL_GetPixelFormatName(SDL_GetWindowPixelFormat(_window)); }

SDL_Rect BasicWindow::DisplayBounds() const {
  SDL_Rect bounds;
  SDL_GetDisplayBounds(SDL_GetWindowDisplayIndex(_window), &bounds);
  return bounds;
}

SDL_Rect BasicWindow::DisplayUsableBounds() const {
  SDL_Rect bounds;
  SDL_GetDisplayUsableBounds(SDL_GetWindowDisplayIndex(_window), &bounds);
  return bounds;
}

SDL_Window *BasicWindow::Handle() const { return _window; }

void BasicWindow::ShowWindow() const { SDL_ShowWindow(_window); }
