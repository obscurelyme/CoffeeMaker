#ifndef _animations_enemy_entrance_hpp
#define _animations_enemy_entrance_hpp

#include <functional>

#include "Event.hpp"
#include "Math.hpp"
#include "Spline.hpp"
#include "Utilities.hpp"

namespace Animations {
  class BaseSplineAnimation {
    using Vec2 = CoffeeMaker::Math::Vector2D;

    public:
    explicit BaseSplineAnimation(float animationDuration);
    ~BaseSplineAnimation();

    void Update(float deltaTime);
    Vec2 Position() const;
    void Reset();
    void DebugRender() const;
    bool Complete() const;

    void OnStart(std::function<void(void *)>);
    void OnComplete(std::function<void(void *)>);

    protected:
    void ProcessStart();
    void ProcessComplete();

    Scope<CoffeeMaker::Spline> _spline;
    std::vector<std::function<void(void *)>> _startListeners;
    std::vector<std::function<void(void *)>> _completeListeners;
  };

  class SplineAnimation {
    public:
    SplineAnimation();
    ~SplineAnimation();
    void OnStart(std::function<void(void *)>);
    void OnComplete(std::function<void(void *)>);

    protected:
    std::vector<std::function<void(void *)>> _startListeners;
    std::vector<std::function<void(void *)>> _completeListeners;
  };

  class EnemyEntrance : public BaseSplineAnimation {
    public:
    EnemyEntrance();
    ~EnemyEntrance() = default;
  };

  class EnemyEntrance001 : public SplineAnimation {
    public:
    explicit EnemyEntrance001(float duration = 1.75f);
    EnemyEntrance001(bool inverted, float duration = 1.75f);
    ~EnemyEntrance001() = default;

    void Reset();
    void Update(float deltaTime);
    CoffeeMaker::Math::Point2D CurrentPosition();
    void SetFinalPosition(const CoffeeMaker::Math::Point2D &pos);

    private:
    float _inverted;
    float _knot;
    float _currentTime;
    float _duration;
    CoffeeMaker::Math::Point2D _currentPoint;

    static Scope<CoffeeMaker::BSpline> _bSpline;
    static Scope<CoffeeMaker::BSpline> _bSplineInverted;
    static void LoadBSpline();
  };

  /**
   * @brief Enemies travel along the north side of the screen, never
   * interfering with the player's path.
   */
  class EnemyBriefEntrance : public BaseSplineAnimation {
    public:
    EnemyBriefEntrance();
    ~EnemyBriefEntrance() = default;
  };

  /**
   * @brief Enemies exit towards the bottom of the screen. They will collide with
   * the player if on a collision path.
   */
  class EnemyExit : public BaseSplineAnimation {
    public:
    EnemyExit();
    ~EnemyExit() = default;
  };

}  // namespace Animations

#endif
