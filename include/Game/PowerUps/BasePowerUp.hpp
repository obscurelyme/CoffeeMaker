#ifndef _basepowerup_hpp
#define _basepowerup_hpp

#include "Async.hpp"
#include "Audio.hpp"
#include "Event.hpp"
#include "Game/Entity.hpp"
#include "Game/Events.hpp"
#include "Logger.hpp"

namespace UCI {
  class PowerUp : public CoffeeMaker::UserEventEmitter {
    public:
    enum PowerUpType { Warp = 999999 };

    public:
    PowerUp(){};
    PowerUp(float, float){};
    virtual ~PowerUp(){};

    virtual void Use() = 0;

    protected:
    float _enableDuration;
    float _rechargeDuration;
    Scope<CoffeeMaker::Async::TimeoutTask> _enableTimeout;
    Scope<CoffeeMaker::Async::TimeoutTask> _rechargeTimeout;
    Scope<CoffeeMaker::AudioElement> _enabledSoundEffect;
    Scope<CoffeeMaker::AudioElement> _disabledSoundEffect;
  };

  class PowerMissle;
  class MineBomb;
  class ForceShield;

  class Warp : public PowerUp, CoffeeMaker::IUserEventListener {
    public:
    Warp() : _charges(3) {
      _enabledSoundEffect = CreateScope<CoffeeMaker::AudioElement>("effects/Warp.ogg");
      _enableTimeout = CreateScope<CoffeeMaker::Async::TimeoutTask>(
          "[POWER_UP][WARP][ENABLED]",
          [] { CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_POWER_UP_LOST, PowerUpType::Warp); }, 250);
      _rechargeTimeout = CreateScope<CoffeeMaker::Async::TimeoutTask>(
          "[POWER_UP][WARP][RECHARGE_TIMER]",
          [] { CoffeeMaker::PushUserEvent(UCI::Events::PLAYER_POWER_UP_RECHARGED, PowerUpType::Warp); }, 5000);
    }

    virtual void Use() {
      if (_charges > 0) {
        _charges--;
        EmitUserEvent(UCI::Events::PLAYER_POWER_UP_GAINED, PowerUpType::Warp);
        _enableTimeout->Start();
        _enabledSoundEffect->Play();
        if (_charges == 0) {
          CoffeeMaker::Logger::Debug("[PLAYER_EVENT][PLAYER_POWER_UP_RECHARGING][WARP]");
          _rechargeTimeout->Start();
        }
      }
    }

    virtual void OnSDLUserEvent(const SDL_UserEvent& event) {
      if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE) {
        _rechargeTimeout->Pause();
        return;
      }

      if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE) {
        _rechargeTimeout->Unpause();
        return;
      }

      if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_UNLOAD) {
        _rechargeTimeout->Cancel();
        return;
      }

      if (event.type == UCI::Events::PLAYER_POWER_UP_RECHARGED && event.code == PowerUpType::Warp) {
        _charges = 3;
        CoffeeMaker::Logger::Debug("[PLAYER_EVENT][PLAYER_POWER_UP_RECHARGED][WARP]");
        return;
      }
    }

    private:
    unsigned int _charges;
    Scope<CoffeeMaker::Async::TimeoutTask> _recharge2Timeout;
    Scope<CoffeeMaker::Async::TimeoutTask> _recharge3Timeout;
  };
}  // namespace UCI

#endif
