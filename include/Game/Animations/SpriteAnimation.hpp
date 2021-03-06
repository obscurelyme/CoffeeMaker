#ifndef _sprite_animation_hpp
#define _sprite_animation_hpp

#include <functional>

#include "Sprite.hpp"
#include "Timer.hpp"
#include "Utilities.hpp"

namespace Animations {

  /**
   * @brief Using a spritesheet, set up frames that will be cycled through
   * over a given time period.
   */
  class SpriteAnimation {
    public:
    SpriteAnimation(Ref<CoffeeMaker::Sprite> sprite, int duration, int loops);
    ~SpriteAnimation();

    void AddFrame(SDL_Rect frame);
    void Start();
    void Stop();
    void Render();
    void Pause();
    void Unpause();
    void OnComplete(std::function<void(void)> callback);

    static void ProcessSpriteAnimations();

    private:
    void Update();

    Ref<CoffeeMaker::Sprite> _sprite;
    int _duration;
    int _loops;
    bool _started;
    std::vector<SDL_Rect> _frames;
    int _durationPerFrame;
    Scope<CoffeeMaker::StopWatch> _stopwatch;
    unsigned int _currentFrame;
    int _id;
    std::function<void(void)> _onCompleteCallback;

    static std::vector<SpriteAnimation*> _animations;
    static int _uid;
  };

}  // namespace Animations

#endif
