#ifndef _coffeemaker_spline_hpp
#define _coffeemaker_spline_hpp

#include <vector>

#include "Math.hpp"

namespace CoffeeMaker {
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
