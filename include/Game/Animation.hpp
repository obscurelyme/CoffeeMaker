#ifndef _animation_hpp
#define _animation_hpp

#include <vector>

class AnimationState {
  public:
  AnimationState* Next() const;
  AnimationState* Previous() const;

  private:
  AnimationState* _next;
  AnimationState* _prev;
};

class Animation {
  public:
  Animation();
  ~Animation() = default;

  void AppendState(const AnimationState& state);
  void SetState(const AnimationState& state);
  void NextState();
  void GetState() const;

  private:
  std::vector<AnimationState* const> _animationStates;
};

#endif
