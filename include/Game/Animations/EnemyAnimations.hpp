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

    void OnStart(std::function<void(void*)>);
    void OnComplete(std::function<void(void*)>);

    protected:
    void ProcessStart();
    void ProcessComplete();

    Scope<CoffeeMaker::Spline> _spline;
    std::vector<std::function<void(void*)>> _startListeners;
    std::vector<std::function<void(void*)>> _completeListeners;
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
