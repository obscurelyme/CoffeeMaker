#include "FPS.hpp"

#include <memory>

#include "Color.hpp"
#include "FontManager.hpp"

using namespace CoffeeMaker;
using namespace CoffeeMaker::UIProperties;

FPS::FPS() : _text(std::make_shared<Text>("00")) {
  _priorTime = SDL_GetTicks();
  _currentTime = _priorTime;

  _text->SetFont(FontManager::UseFont("Sarpanch/Sarpanch-Regular"));
  _text->SetColor(Color(255, 255, 0, 255));  // Yellow
  _text->SetHorizontalAlignment(HorizontalAlignment::Centered);
  _text->SetVerticalAlignment(VerticalAlignment::Centered);
  _view.AppendChild(_text);
  _view.SetVerticalAlignment(VerticalAlignment::Bottom);
}

FPS::~FPS() {}

void FPS::Update() {
  _countedFrames++;
  _currentTime = SDL_GetTicks();

  if (_currentTime - _priorTime >= _msInASecond) {
    _text->SetText(std::to_string(_countedFrames));
    _priorTime = _currentTime;
    _countedFrames = 0;
  }
}

void FPS::Render() { _view.Render(); }
