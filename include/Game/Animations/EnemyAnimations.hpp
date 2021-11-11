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
    void Start();
    void Reset();
    void DebugRender() const;
    bool Complete() const;

    void OnStart(std::function<void(void*)>);
    void OnComplete(std::function<void(void*)>);

    protected:
    void ProcessStart();
    void ProcessComplete();

    Scope<CoffeeMaker::Spline> _spline;
    std::vector<std::function<void(void*)>> _startListeners;
    std::vector<std::function<void(void*)>> _completeListeners;
  };

  /**
   * @brief Enemies do a double loop traveling down the screen towards the player.
   * Enemies will collide with the player if possible.
   */
  class EnemyEntrance : public BaseSplineAnimation {
    public:
    EnemyEntrance();
    ~EnemyEntrance() = default;
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
