#include "FontManager.hpp"
#include "FPS.hpp"
#include "Color.hpp"

using namespace CoffeeMaker;

FPS::FPS() {
  _priorTime = SDL_GetTicks();
  _currentTime = _priorTime;

  _textView.SetFont(FontManager::UseFont("Roboto/Roboto-Regular"));
  _textView.SetText("00");
  _textView.SetColor(Color(255, 255, 0, 255)); // Yellow
  _textView.SetXAlignment(TextAlignmentX::Centered);
  _textView.SetYAlignment(TextAlignmentY::BottomAligned);
  _view.AppendChild(&_textView);
}

FPS::~FPS() {}

void FPS::Update() {
  _countedFrames++;
  _currentTime = SDL_GetTicks();

  if (_currentTime - _priorTime >= _msInASecond) {
    _textView.SetText(std::to_string(_countedFrames));
    _priorTime = _currentTime;
    _countedFrames = 0;
  }
}

void FPS::Render() {
  _view.Render();
}
