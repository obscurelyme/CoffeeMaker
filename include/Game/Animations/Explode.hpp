#ifndef _animations_explode_hpp
#define _animations_explode_hpp

#include "Event.hpp"
#include "Game/Animations/SpriteAnimation.hpp"
#include "Math.hpp"
#include "Utilities.hpp"

namespace UCI {
  namespace Animations {
    using Vec2 = CoffeeMaker::Math::Vector2D;
    class ExplodeSpriteAnimation : public CoffeeMaker::IUserEventListener {
      public:
      ExplodeSpriteAnimation();
      ~ExplodeSpriteAnimation();

      void Render();
      void Start();
      void Stop();
      void SetPosition(const Vec2& pos);
      void OnComplete(std::function<void(void)> callback);
      virtual void OnSDLUserEvent(const SDL_UserEvent& event);

      private:
      static Ref<CoffeeMaker::Sprite> _sprite;
      Scope<::Animations::SpriteAnimation> _animation;
      Vec2 _position;
    };
  }  // namespace Animations
}  // namespace UCI

#endif
