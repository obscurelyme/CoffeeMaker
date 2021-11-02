#ifndef _animations_enemy_entrance_hpp
#define _animations_enemy_entrance_hpp

#include "Math.hpp"
#include "Spline.hpp"
#include "Utilities.hpp"

namespace Animations {
  class BaseSplineAnimation {
    using Vec2 = CoffeeMaker::Math::Vector2D;

    public:
    explicit BaseSplineAnimation(float animationDuration);
    ~BaseSplineAnimation() = default;

    void Update(float deltaTime);
    Vec2 Position() const;
    void Reset();
    void DebugRender() const;
    bool Complete() const;

    protected:
    Scope<CoffeeMaker::Spline> _spline;
  };

  class EnemyEntrance : public BaseSplineAnimation {
    public:
    EnemyEntrance();
    ~EnemyEntrance() = default;
  };

  class EnemyExit : public BaseSplineAnimation {
    public:
    EnemyExit();
    ~EnemyExit() = default;
  };
}  // namespace Animations

#endif
