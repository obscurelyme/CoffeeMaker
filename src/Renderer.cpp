#include "Renderer.hpp"

#include "Logger.hpp"
#include "Window.hpp"

using namespace CoffeeMaker;

SDL_Renderer *Renderer::_renderer = nullptr;

Uint32 Renderer::_numDrawCalls = 0;
int Renderer::_width = 0;
int Renderer::_height = 0;
SDL_BlendMode Renderer::_blendMode = SDL_BLENDMODE_NONE;

Renderer::Renderer() {
  if (_renderer == nullptr) {
    _renderer = SDL_CreateRenderer(GlobalWindow::Instance()->Handle(), -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_GetRendererOutputSize(_renderer, &_width, &_height);
    SDL_Rect vp;
    SDL_RenderGetViewport(Renderer::Instance(), &vp);
    CM_LOGGER_INFO("Renderer created with output size: ({}, {})", _width, _height);
    CM_LOGGER_INFO("Renderer current viewport size: ({}, {})", vp.w, vp.h);
    SDL_GetRenderDrawBlendMode(_renderer, &_blendMode);
    CM_LOGGER_INFO("Renderer blend mode: {}", _blendMode);
  }
}

Renderer::~Renderer() {
  if (_renderer == nullptr) return;
  Destroy();
}

SDL_Renderer *Renderer::Instance() { return _renderer; }

void Renderer::BeginRender() {
  _numDrawCalls = 0;
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  SDL_RenderClear(_renderer);
}

void Renderer::EndRender() { SDL_RenderPresent(_renderer); }

void Renderer::Destroy() {
  SDL_DestroyRenderer(_renderer);
  _renderer = nullptr;
}

Uint32 Renderer::DrawCalls() { return _numDrawCalls; }

void Renderer::IncDrawCalls() { _numDrawCalls++; }

bool Renderer::Exists() { return _renderer != nullptr; }

int Renderer::GetOutputWidth() { return _width; }

int Renderer::GetOutputHeight() { return _height; }

float Renderer::GetOutputWidthF() { return static_cast<float>(_width); }

float Renderer::GetOutputHeightF() { return static_cast<float>(_height); }
