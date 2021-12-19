#include "Window.hpp"

#include "Logger.hpp"

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

Uint32 GlobalWindow::ID() { return _instance->GetID(); }

std::string ScreenDPI::toString() {
  return fmt::format(fmt::runtime("Diagonal {}, Horizontal {}, Vertical {}"), diagonal, horizontal, vertical);
}

SDL_Window *BasicWindow::_window = nullptr;

BasicWindow::BasicWindow(std::string title, int width, int height, bool fullscreen, bool hdpi) : _highDpiMode(hdpi) {
  int windowFlags = SDL_WINDOW_HIDDEN;

  if (fullscreen) {
    windowFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  if (_highDpiMode) {
    windowFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI;
  }

  if (_highDpiMode && fullscreen) {
    windowFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_FULLSCREEN_DESKTOP;
  }

  _window =
      SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
  _screenDpi = SetScreenDPI();
  _dpiScale = _screenDpi.diagonal / ScreenDPI::BASE_DPI;
  SDL_GetDisplayBounds(SDL_GetWindowDisplayIndex(_window), &_screenBounds);
  SDL_GetDisplayUsableBounds(SDL_GetWindowDisplayIndex(_window), &_usableDisplayBounds);
  CM_LOGGER_INFO("Display DPI Scale: {}", _dpiScale);
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

float BasicWindow::DPIScale() const {
  if (_highDpiMode) {
    return _dpiScale;
  }
  return 1.0f;
}

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

Uint32 BasicWindow::GetID() const { return SDL_GetWindowID(_window); }

bool BasicWindow::HighDPIMode() const { return _highDpiMode; }

std::string CoffeeMaker::UtilityWindow::title = "CoffeeMaker";
int CoffeeMaker::UtilityWindow::width = 800;
int CoffeeMaker::UtilityWindow::height = 600;

CoffeeMaker::UtilityWindow::UtilityWindow() : _handle(nullptr) {
  _handle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                             SDL_WINDOW_HIDDEN);
  if (_handle == NULL) {
    CM_LOGGER_CRITICAL("Could not create utility window.");
  }
  SDL_GetDisplayBounds(SDL_GetWindowDisplayIndex(_handle), &_displayBounds);
  SDL_GetDisplayUsableBounds(SDL_GetWindowDisplayIndex(_handle), &_usableDisplayBounds);
  CM_LOGGER_INFO("Display Usable Bounds: ({},{})", _usableDisplayBounds.w, _usableDisplayBounds.h);
  CM_LOGGER_INFO("Display Bounds: ({},{})", _displayBounds.w, _displayBounds.h);
  SDL_DestroyWindow(_handle);
  _handle = nullptr;
}

CoffeeMaker::UtilityWindow::~UtilityWindow() {}

int CoffeeMaker::UtilityWindow::DisplayHeight() const { return _displayBounds.h; }

int CoffeeMaker::UtilityWindow::DisplayWidth() const { return _displayBounds.w; }
