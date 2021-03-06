#include "Spline.hpp"

#include <SDL2/SDL.h>

#include <fstream>
#include <iostream>

#include "Color.hpp"
#include "MessageBox.hpp"
#include "Renderer.hpp"
#include "Utilities.hpp"

CoffeeMaker::BSpline::BSpline(size_t numControlPoints) :
    _cache({}), _tinysplineBSpline(CreateScope<tinyspline::BSpline>(numControlPoints)), _curves({}) {
  for (size_t i = 0; i < numControlPoints; i++) {
    _tinysplineBSpline->setControlPointAt(i, std::vector<tinyspline::real>{0, 0});
  }
}

CoffeeMaker::BSpline::~BSpline() = default;

void CoffeeMaker::BSpline::Load(const std::string& filePath) {
  std::string fullFilePath = CoffeeMaker::Utilities::AssetsDirectory() + "/" + filePath;
  std::ifstream inf{fullFilePath};
  if (!inf) {
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("Error Reading File",
                                                   "Could not read file: \"" + fullFilePath + "\"");
  }

  std::vector<tinyspline::real> pointsFromFile = {};
  _cache.clear();
  _curves.clear();

  while (inf) {
    std::string input;
    inf >> input;
    if (input != "") {
      pointsFromFile.push_back(std::stod(input));
    }
  }

  _tinysplineBSpline = CreateScope<tinyspline::BSpline>(pointsFromFile.size() / 2);
  SetControlPoints(pointsFromFile);
}

void CoffeeMaker::BSpline::Save() const { _tinysplineBSpline->save("tmp.spline"); }

std::vector<CoffeeMaker::Math::Point2D> CoffeeMaker::BSpline::GetControlPoints() const {
  std::vector<CoffeeMaker::Math::Point2D> points{};
  std::vector<tinyspline::real> controlPoints = _tinysplineBSpline->controlPoints();
  size_t controlPointsSize = controlPoints.size() / static_cast<size_t>(2);

  for (unsigned int i = 0; i < controlPointsSize; i++) {
    points.push_back(CoffeeMaker::Math::Point2D{.x = static_cast<float>(controlPoints[i * 2]),
                                                .y = static_cast<float>(controlPoints[i * 2 + 1])});
  }

  return points;
}

size_t CoffeeMaker::BSpline::NumControlPoints() const { return _tinysplineBSpline->numControlPoints(); }

void CoffeeMaker::BSpline::AddControlPoint(const CoffeeMaker::Math::Point2D& controlPoint) {
  _cache.push_back(controlPoint);
  if (_cache.size() > _tinysplineBSpline->numControlPoints()) {
    // increase size of the spline.
    _tinysplineBSpline = CreateScope<tinyspline::BSpline>(_cache.size());
    SetControlPoints(_cache);
    return;
  }
  SetControlPointAt(_cache.size() - 1, controlPoint);
}

void CoffeeMaker::BSpline::RemoveControlPointAt(size_t) {
  // _cache.erase(_cache.begin() + index);
  // if (_cache.size() < 4) {
  //   _tinysplineBSpline.reset(new tinyspline::BSpline(4));
  // } else {
  //   _tinysplineBSpline.reset(new tinyspline::BSpline(_cache.size()));
  // }
  // SetControlPoints(_cache);
}

void CoffeeMaker::BSpline::SetControlPoints(const std::vector<tinyspline::real>& controlPoints) {
  _tinysplineBSpline->setControlPoints(controlPoints);
}

void CoffeeMaker::BSpline::SetControlPoints(const std::vector<CoffeeMaker::Math::Point2D>& controlPoints) {
  for (size_t i = 0; i < controlPoints.size(); i++) {
    SetControlPointAt(i, controlPoints[i]);
  }
}

void CoffeeMaker::BSpline::SetControlPoints(const std::vector<CoffeeMaker::Math::Vector2D>& controlPoints) {
  for (size_t i = 0; i < controlPoints.size(); i++) {
    SetControlPointAt(i, controlPoints[i]);
  }
}

void CoffeeMaker::BSpline::SetControlPointAt(size_t index, const CoffeeMaker::Math::Vector2D& vector) {
  std::vector<tinyspline::real> pointToAdd{static_cast<tinyspline::real>(vector.x),
                                           static_cast<tinyspline::real>(vector.y)};
  _tinysplineBSpline->setControlPointAt(index, pointToAdd);
}

void CoffeeMaker::BSpline::SetControlPointAt(size_t index, const CoffeeMaker::Math::Point2D& point) {
  std::vector<tinyspline::real> pointToAdd{static_cast<tinyspline::real>(point.x),
                                           static_cast<tinyspline::real>(point.y)};
  _tinysplineBSpline->setControlPointAt(index, pointToAdd);
}

void CoffeeMaker::BSpline::GenerateCurves(size_t precision) {
  _curves.clear();
  std::vector<tinyspline::real> temp = _tinysplineBSpline->sample(precision);
  size_t tempSize = temp.size() / static_cast<size_t>(2);
  for (size_t i = 0; i < tempSize; i++) {
    _curves.push_back(
        CoffeeMaker::Math::Point2D{.x = static_cast<float>(temp[i * 2]), .y = static_cast<float>(temp[i * 2 + 1])});
  }
}

std::vector<CoffeeMaker::Math::Point2D> CoffeeMaker::BSpline::InvertControlPoints() {
  std::vector<CoffeeMaker::Math::Point2D> controlPoints = GetControlPoints();
  std::vector<CoffeeMaker::Math::Point2D> invertedPoints = {};

  for (size_t i = 0; i < controlPoints.size(); i++) {
    invertedPoints.push_back(controlPoints[i]);
    invertedPoints[i].x = CoffeeMaker::Renderer::GetOutputWidth() - invertedPoints[i].x;
  }

  return invertedPoints;
}

std::vector<CoffeeMaker::Math::Point2D> CoffeeMaker::BSpline::GetPoints() const { return _curves; }

CoffeeMaker::Math::Point2D CoffeeMaker::BSpline::Point2DAtKnot(tinyspline::real knot) {
  tinyspline::real filteredKnot = std::clamp(knot, 0.0, 1.0);
  std::vector<tinyspline::real> temp = _tinysplineBSpline->eval(filteredKnot).result();
  return CoffeeMaker::Math::Point2D{.x = static_cast<float>(temp[0]), .y = static_cast<float>(temp[1])};
}

void CoffeeMaker::BSpline::SetKnotAt(size_t index, tinyspline::real knot) {
  tinyspline::real clampedKnot = std::clamp(knot, 0.0, 1.0);
  std::vector<tinyspline::real> allKnots = _tinysplineBSpline->knots();
  _tinysplineBSpline->setKnotAt(index, clampedKnot);
}

void CoffeeMaker::BSpline::RemapControlPoints() {
  using Pt2 = CoffeeMaker::Math::Point2D;
  using namespace CoffeeMaker::Math;

  std::vector<Pt2> remappedPoints = {};
  std::vector<Pt2> currentPoints = GetControlPoints();
  for (size_t i = 0; i < currentPoints.size(); i++) {
    remappedPoints.push_back(
        Pt2{.x = Remap(0.0f, 2560.0f, 0.0f, CoffeeMaker::Renderer::GetOutputWidthF(), currentPoints[i].x),
            .y = Remap(0.0f, 1440.0f, 0.0f, CoffeeMaker::Renderer::GetOutputHeightF(), currentPoints[i].y)});
  }

  SetControlPoints(remappedPoints);
}

CoffeeMaker::Spline::Spline() :
    _spline({}),
    _currentSegment({}),
    _time(3.0f),
    _offset(0),
    _currentTime(0),
    _finalOffset(0),
    _complete(false),
    _weight(0.0f) {}

CoffeeMaker::Spline::Spline(float animationTime) :
    _spline({}),
    _currentSegment({}),
    _time(animationTime),
    _offset(0),
    _currentTime(0),
    _finalOffset(0),
    _complete(false),
    _weight(0.0f) {}

CoffeeMaker::Spline::~Spline() {
  _trail.clear();
  _currentSegment.clear();
  _spline.clear();
}

void CoffeeMaker::Spline::AddCurve(const Vec2& start, const Vec2& control1, const Vec2& control2, const Vec2& end) {
  _spline.emplace_back(start);
  _spline.emplace_back(control1);
  _spline.emplace_back(control2);
  _spline.emplace_back(end);
  _finalOffset = static_cast<unsigned int>(_spline.size());
}

float CoffeeMaker::Spline::Weight() { return _spline.size() / 4.0f; }

void CoffeeMaker::Spline::Start() {
  _currentSegment.emplace_back(_spline.at(0));
  _currentSegment.emplace_back(_spline.at(1));
  _currentSegment.emplace_back(_spline.at(2));
  _currentSegment.emplace_back(_spline.at(3));
  _offset = 0;
}

void CoffeeMaker::Spline::Reset() {
  _trail.clear();
  _currentSegment.clear();
  Start();
  _complete = false;
  _currentTime = 0;
  _weight = 0;
}

bool CoffeeMaker::Spline::IsComplete() const { return _complete; }

void CoffeeMaker::Spline::Update(float deltaTime) {
  _currentTime += deltaTime;
  _weight = _currentTime / (_time / (_spline.size() * 0.25f));

  if (_weight >= 1.0f && !_complete) {
    _currentTime = 0;
    _offset += 4;
    _weight = 0;
    // Are we done?
    if (_offset == _finalOffset) {
      _complete = true;
      return;
    }
    _currentSegment.clear();
    _currentSegment.emplace_back(_spline.at(_offset));
    _currentSegment.emplace_back(_spline.at(_offset + 1));
    _currentSegment.emplace_back(_spline.at(_offset + 2));
    _currentSegment.emplace_back(_spline.at(_offset + 3));
  }
}

void CoffeeMaker::Spline::DebugRender() const {
  // Debug Bezier Curve
  for (auto& point : _trail) {
    SDL_SetRenderDrawColor(CoffeeMaker::Renderer::Instance(), CoffeeMaker::Colors::Yellow.r,
                           CoffeeMaker::Colors::Yellow.g, CoffeeMaker::Colors::Yellow.b, CoffeeMaker::Colors::Yellow.a);
    SDL_RenderDrawPointF(CoffeeMaker::Renderer::Instance(), point.x, point.y);
    CoffeeMaker::Renderer::IncDrawCalls();
  }
}

CoffeeMaker::Math::Vector2D CoffeeMaker::Spline::CurrentPosition() {
  using Vec2 = CoffeeMaker::Math::Vector2D;
  if (_complete) {
    return _spline.at(_spline.size() - 1);
  }
  Vec2 p = CoffeeMaker::Math::CubicBezierCurve(_currentSegment[0], _currentSegment[1], _currentSegment[2],
                                               _currentSegment[3], _weight);
  // NOTE: nice for debugging, but when the game is paused this could lead to a soft memory leak.
  // _trail.emplace_back(p);
  return p;
}
