#ifndef _basepowerup_hpp
#define _basepowerup_hpp

#include "Timer.hpp"

class PowerUp {
  public:
  PowerUp(float enableDuration, float rechargeDuration);
  virtual ~PowerUp();

  virtual void Recharge() = 0;
  virtual void Use() = 0;

  protected:
  CoffeeMaker::Timeout _timeout;
};

class PowerMissle;
class MineBomb;
class Warp;
class ForceShield;

#endif
