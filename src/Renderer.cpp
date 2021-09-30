#include "Renderer.hpp"

#include "Window.hpp"

using namespace CoffeeMaker;

SDL_Renderer *Renderer::_renderer = nullptr;

Renderer::Renderer() {
  if (_renderer == nullptr) {
    _renderer = SDL_CreateRenderer(GlobalWindow::Instance()->Handle(), -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  }
}

Renderer::~Renderer() {
  if (_renderer == nullptr) return;
  Destroy();
}

SDL_Renderer *Renderer::Instance() { return _renderer; }

void Renderer::BeginRender() {
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  SDL_RenderClear(_renderer);
}

void Renderer::EndRender() { SDL_RenderPresent(_renderer); }

void Renderer::Destroy() {
  SDL_DestroyRenderer(_renderer);
  _renderer = nullptr;
}
