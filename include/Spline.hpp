#ifndef _coffeemaker_spline_hpp
#define _coffeemaker_spline_hpp

#include <vector>

#include "Math.hpp"
#include "Utilities.hpp"
#include "tinysplinecxx.h"

namespace CoffeeMaker {
  /**
   * @brief BSpline class, leverages De Boor's algorithm to compute B-Splines.
   */
  class BSpline {
    public:
    explicit BSpline(size_t numControlPoints = 4);
    ~BSpline();

    inline std::vector<CoffeeMaker::Math::Point2D> GetControlPoints() const {
      std::vector<CoffeeMaker::Math::Point2D> points{};
      std::vector<tinyspline::real> controlPoints = _tinysplineBSpline->controlPoints();

      for (unsigned int i = 0; i < controlPoints.size() / 2; i++) {
        points.push_back(CoffeeMaker::Math::Point2D{.x = static_cast<float>(controlPoints[i]),
                                                    .y = static_cast<float>(controlPoints[i + 1])});
      }

      return points;
    }

    void SetControlPoints(const std::vector<tinyspline::real>& controlPoints) {
      _tinysplineBSpline->setControlPoints(controlPoints);
    }
    void SetControlPointAt(unsigned long index, CoffeeMaker::Math::Vector2D vector) {
      std::vector<tinyspline::real> pointToAdd{static_cast<tinyspline::real>(vector.x),
                                               static_cast<tinyspline::real>(vector.y)};
      _tinysplineBSpline->setControlPointAt(index, pointToAdd);
    }
    void SetControlPointAt(unsigned long index, CoffeeMaker::Math::Point2D point) {
      std::vector<tinyspline::real> pointToAdd{static_cast<tinyspline::real>(point.x),
                                               static_cast<tinyspline::real>(point.y)};
      _tinysplineBSpline->setControlPointAt(index, pointToAdd);
    }

    private:
    Scope<tinyspline::BSpline> _tinysplineBSpline;
  };

  /**
   * @brief Spline class, combines bezier curves into multiple splines using
   * de Casteljau's algorithm.
   * @deprecated Leverage CoffeeMaker::BSpline instead, which uses De Boor's algorithm.
   */
  class Spline {
    using Vec2 = CoffeeMaker::Math::Vector2D;

    public:
    Spline();
    explicit Spline(float animationTime);
    ~Spline();

    /**
     * @brief Adds a curve to the spline.
     */
    void AddCurve(const Vec2&, const Vec2&, const Vec2&, const Vec2&);
    /**
     * @brief Returns the current calculated weight of the current segment.
     *
     * @return float
     */
    float Weight();
    /**
     * @brief Returns the current position within the spline
     * given the current calculated weight.
     *
     * @return CoffeeMaker::Math::Vector2D
     */
    Vec2 CurrentPosition();

    void Update(float deltaTime);
    void Start();
    void Reset();
    bool IsComplete() const;
    void SetAnimationTime();
    void DebugRender() const;

    private:
    std::vector<Vec2> _spline;
    std::vector<Vec2> _currentSegment;
    float _time;
    unsigned int _offset;
    float _currentTime;
    unsigned int _finalOffset;
    bool _complete;
    float _weight;

    /**
     * @brief Holds a cache of each Vec2 for debugging purposes.
     */
    std::vector<Vec2> _trail;
  };
}  // namespace CoffeeMaker

#endif
