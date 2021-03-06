#include "Game/Scenes/SplineBuilder.hpp"

#include <iostream>
#include <string>

#include "InputManager.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"

SplineBuilder::SplineBuilder() :
    _backgroundColor(CoffeeMaker::Colors::Black),
    _bSpline(nullptr),
    _bSplineCurvePoints({}),
    _bSplineControlPoints({}),
    _current(0) {}

SplineBuilder::~SplineBuilder() {}

void SplineBuilder::Render() {
  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), _backgroundColor.r, _backgroundColor.g, _backgroundColor.b,
                         _backgroundColor.a);
  SDL_RenderClear(CoffeeMaker::Renderer::Instance());

  for (auto& v : _bSplineControlPoints) {
    v->Render();
  }

  SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), 255, 255, 255, 255);
  for (auto& curvePoint : _bSplineCurvePoints) {
    SDL_FRect s = SDL_FRect{.x = curvePoint.x, .y = curvePoint.y, .w = 1, .h = 1};
    SDL_RenderFillRectF(CoffeeMaker::Renderer::Instance(), &s);
  }
}

void SplineBuilder::Update(float) {
  for (auto& v : _bSplineControlPoints) {
    v->Update();
  }

  if (CoffeeMaker::InputManager::IsKeyHeld(SDL_SCANCODE_ESCAPE)) {
    CoffeeMaker::PushCoffeeMakerEvent(CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_QUIT);
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_C)) {
    // clear the points
    _bSplineControlPoints.clear();
    _bSplineCurvePoints.clear();
    _bSpline = CreateScope<CoffeeMaker::BSpline>();
    _current = 0;
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_R)) {
    if (_bSpline != nullptr) {
      std::vector<tinyspline::real> knot = _bSpline->GetKnots();
      for (auto& k : knot) {
        std::cout << k << std::endl;
      }
    }
  }

  if (CoffeeMaker::InputManager::IsKeyPressed(SDL_SCANCODE_S)) {
    if (_bSpline != nullptr) {
      _bSpline->Save();
    }
  }
}

void SplineBuilder::Init() {
  _bSpline = CreateScope<CoffeeMaker::BSpline>();
  Scope<CoffeeMaker::BSpline> _bSplineInverted;
  _bSpline->Load("splines/flyby.spline");
  _bSpline->RemapControlPoints();
  _bSpline->GenerateCurves();
  _bSplineInverted = CreateScope<CoffeeMaker::BSpline>(_bSpline->NumControlPoints());
  _bSplineInverted->SetControlPoints(_bSpline->InvertControlPoints());
  _bSplineInverted->GenerateCurves();

  _bSplineCurvePoints = _bSpline->GetPoints();
  for (auto p : _bSplineInverted->GetPoints()) {
    _bSplineCurvePoints.emplace_back(p);
  }
}
void SplineBuilder::Destroy() {}
void SplineBuilder::Pause() {}
void SplineBuilder::Unpause() {}

void SplineBuilder::OnSDLUserEvent(const SDL_UserEvent&) {}

void SplineBuilder::OnMouseDown(const SDL_MouseButtonEvent& event) {
  if (CoffeeMaker::InputManager::IsKeyDown(SDL_SCANCODE_LSHIFT) && event.button == SDL_BUTTON_LEFT &&
      _bSpline != nullptr) {
    Ref<SplinePoint> splinePoint =
        CreateRef<SplinePoint>(static_cast<float>(event.x), static_cast<float>(event.y), _current);
    splinePoint->OnDrag([this](size_t i, float x, float y) {
      _bSpline->SetControlPointAt(i, CoffeeMaker::Math::Point2D{.x = x, .y = y});
      if (_current >= 4) {
        _bSpline->GenerateCurves();
        _bSplineCurvePoints = _bSpline->GetPoints();
      }
    });

    _bSplineControlPoints.push_back(splinePoint);
    _bSpline->AddControlPoint(splinePoint->GetPoint());
    _current++;
    if (_current >= 4) {
      _bSpline->GenerateCurves();
      _bSplineCurvePoints = _bSpline->GetPoints();
    }
  }
}

void SplineBuilder::OnMouseUp(const SDL_MouseButtonEvent&) {}
void SplineBuilder::OnMouseWheel(const SDL_MouseWheelEvent&) {}
void SplineBuilder::OnMouseMove(const SDL_MouseMotionEvent&) {}
