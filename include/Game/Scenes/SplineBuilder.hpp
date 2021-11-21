#ifndef _splinebuilder_hpp
#define _splinebuilder_hpp

#include <SDL2/SDL.h>

#include <vector>

#include "Color.hpp"
#include "Event.hpp"
#include "Game/Scene.hpp"
#include "InputManager.hpp"
#include "Math.hpp"
#include "Renderer.hpp"
#include "Spline.hpp"
#include "Utilities.hpp"
#include "tinysplinecxx.h"

class SplinePoint : public CoffeeMaker::IMouseListener {
  public:
  SplinePoint(float xPos, float yPos) :
      _selected(false),
      _rect(SDL_FRect{.w = 8, .h = 8, .x = xPos, .y = yPos}),
      _point(CoffeeMaker::Math::Point2D{.x = xPos, .y = yPos, .weight = 1.0f}) {}
  ~SplinePoint() = default;
  void Render() {
    if (_selected) {
      SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 255, 255, 0, 255);
      SDL_RenderFillRectF(CoffeeMaker::Renderer::Instance(), &_rect);
    } else {
      SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 255, 255, 255, 255);
      SDL_RenderDrawRectF(CoffeeMaker::Renderer::Instance(), &_rect);
    }
  }

  void Update() {
    if (_selected) {
      if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_UP)) {
        _point.y--;
        _rect.y = _point.y;
      }

      if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_DOWN)) {
        _point.y++;
        _rect.y = _point.y;
      }

      if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_LEFT)) {
        _point.x--;
        _rect.x = _point.x;
      }

      if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_RIGHT)) {
        _point.x++;
        _rect.x = _point.x;
      }
    }
  }

  virtual void OnMouseDown(const SDL_MouseButtonEvent& event) {
    if (event.x <= _rect.w + _rect.x && event.x >= _rect.x && event.y >= _rect.y && event.y <= _rect.y + _rect.h) {
      _selected = true;
    } else {
      _selected = false;
    }
  }

  void SetPoint(const CoffeeMaker::Math::Point2D& point) { _point = point; }

  virtual void OnMouseUp(const SDL_MouseButtonEvent&) {}

  virtual void OnMouseWheel(const SDL_MouseWheelEvent&) {}
  virtual void OnMouseMove(const SDL_MouseMotionEvent&) {}

  private:
  bool _selected;
  SDL_FRect _rect;
  CoffeeMaker::Math::Point2D _point;
};

class SplineBuilder : public Scene, public CoffeeMaker::IMouseListener {
  public:
  SplineBuilder();
  virtual ~SplineBuilder();

  virtual void Render();
  virtual void Update(float deltaTime);
  virtual void Init();
  virtual void Destroy();
  virtual void Pause();
  virtual void Unpause();

  virtual void OnSDLUserEvent(const SDL_UserEvent& event);
  virtual void OnMouseDown(const SDL_MouseButtonEvent& event);
  virtual void OnMouseUp(const SDL_MouseButtonEvent& event);
  virtual void OnMouseWheel(const SDL_MouseWheelEvent& event);
  virtual void OnMouseMove(const SDL_MouseMotionEvent& event);

  private:
  SDL_Color _backgroundColor;
  Scope<CoffeeMaker::Spline> _spline;
  std::vector<CoffeeMaker::Math::Vector2D> _vec2;
  std::vector<CoffeeMaker::Math::Point2D> _points;
  std::vector<CoffeeMaker::Math::Point2D> _spline2;
  std::vector<Ref<SplinePoint>> _splinePoints;
  std::vector<tinyspline::real> _bezierSplinePoints;
  Scope<tinyspline::BSpline> _bspline;
  unsigned int _current;
  std::vector<CoffeeMaker::Math::Point2D> _bsplineConPts;
};

#endif
