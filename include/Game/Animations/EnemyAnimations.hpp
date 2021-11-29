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
    ~SplineAnimation() = default;
    void OnStart(std::function<void(void *)>);
    void OnComplete(std::function<void(void *)>);

    protected:
    std::vector<std::function<void(void *)>> _startListeners;
    std::vector<std::function<void(void *)>> _completeListeners;
  };

  /**
   * @brief Enemies do a double loop traveling down the screen towards the player.
   * Enemies will collide with the player if possible.
   * 0,
        0,
        28,
        111,
        50,
        220,
        80,
        327,
        117,
        421,
        189,
        446,
        249,
        408,
        263,
        362,s
        266,
        287,
        179,
        252,
        134,
        273,s
        109,
        318,x
        110,
        358,s
        122,
        392,s
        151,
        417,s
        230,
        405,s
        273,
        347,s
        298,
        295,s
        297,
        235,s
        263,
        195,s
        196,
        181,s
        150,
        228,d
        152,
        299,s
        174,
        329,d
        246,
        336,
        308,
        288,
        344,
        225,
        366,
        171,
        403,
        93,
        421,
        63
   */
  class EnemyEntrance : public BaseSplineAnimation {
    public:
    EnemyEntrance();
    ~EnemyEntrance() = default;
  };

  class EnemyEntrance001 : public SplineAnimation {
    public:
    EnemyEntrance001(float duration = 1.75f);
    ~EnemyEntrance001() = default;

    void Reset();
    void Update(float deltaTime);
    CoffeeMaker::Math::Point2D CurrentPosition();
    void SetFinalPosition(const CoffeeMaker::Math::Point2D &pos);

    private:
    float _knot;
    float _currentTime;
    float _duration;
    Scope<CoffeeMaker::BSpline> _bSpline;
    CoffeeMaker::Math::Point2D _currentPoint;
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
