#ifndef _splinebuilder_hpp
#define _splinebuilder_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <vector>

#include "Color.hpp"
#include "Event.hpp"
#include "Game/Scene.hpp"
#include "InputManager.hpp"
#include "Math.hpp"
#include "Renderer.hpp"
#include "Spline.hpp"
#include "Utilities.hpp"

class SplinePoint : public CoffeeMaker::IMouseListener {
  public:
  SplinePoint(float xPos, float yPos, size_t index) :
      _selected(false),
      _rect(SDL_FRect{.x = xPos, .y = yPos, .w = 8, .h = 8}),
      _point(CoffeeMaker::Math::Point2D{.x = xPos, .y = yPos}),
      _dragListeners({}),
      _index(index),
      _knot(0.0) {}
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
        //_knot = std::min(_knot + 0.1, 1.0);
        _knot += 0.1;
        HandleKnot();
      }
      if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_DOWN)) {
        // _knot = std::max(_knot - 0.1, 0.0);
        _knot -= 0.1;
        HandleKnot();
      }
    }
  }

  CoffeeMaker::Math::Point2D GetPoint() const { return _point; }

  void OnKnotChange(std::function<void(size_t, double)> fn) { _knotListeners.push_back(fn); }
  void HandleKnot() {
    for (auto& knot : _knotListeners) {
      std::invoke(knot, _index, _knot);
    }
  }

  void OnDrag(std::function<void(size_t, float, float)> fn) { _dragListeners.push_back(fn); }
  void HandleDrag() {
    for (auto& drag : _dragListeners) {
      std::invoke(drag, _index, _point.x, _point.y);
    }
  }

  virtual void OnMouseDown(const SDL_MouseButtonEvent& event) {
    if (event.button == SDL_BUTTON_LEFT) {
      if (event.x <= _rect.w + _rect.x && event.x >= _rect.x && event.y >= _rect.y && event.y <= _rect.y + _rect.h) {
        _selected = true;
      }
    }
  }

  virtual void OnMouseUp(const SDL_MouseButtonEvent& event) {
    if (event.button == SDL_BUTTON_LEFT) {
      _selected = false;
    }
  }

  virtual void OnMouseWheel(const SDL_MouseWheelEvent&) {}

  virtual void OnMouseMove(const SDL_MouseMotionEvent& event) {
    if (_selected) {
      _point.x = static_cast<float>(event.x);
      _point.y = static_cast<float>(event.y);
      _rect.x = _point.x;
      _rect.y = _point.y;
      HandleDrag();
    }
  }

  private:
  bool _selected;
  SDL_FRect _rect;
  CoffeeMaker::Math::Point2D _point;
  std::vector<std::function<void(size_t, float, float)>> _dragListeners;
  std::vector<std::function<void(size_t, double)>> _knotListeners;
  size_t _index;
  double _knot;
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
  Scope<CoffeeMaker::BSpline> _bSpline;
  std::vector<CoffeeMaker::Math::Point2D> _bSplineCurvePoints;
  std::vector<Ref<SplinePoint>> _bSplineControlPoints;
  unsigned int _current;
};

#endif
