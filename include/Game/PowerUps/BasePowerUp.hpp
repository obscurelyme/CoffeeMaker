#ifndef _basepowerup_hpp
#define _basepowerup_hpp

#include <atomic>

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

  class PowerUpCharge : public CoffeeMaker::UserEventEmitter {
    public:
    PowerUpCharge(PowerUp::PowerUpType type, float duration, float cooldownDuration) :
        _onCooldown(false), _powerUpType(type) {
      durationTimer = CreateScope<CoffeeMaker::Async::TimeoutTask>(
          "PowerUpEnabled", [this] { EmitUserEvent(UCI::Events::PLAYER_POWER_UP_LOST, _powerUpType); }, duration);
      cooldownTimer = CreateScope<CoffeeMaker::Async::TimeoutTask>(
          "PowerUpCooldown",
          [this] {
            _onCooldown = false;
            EmitUserEvent(UCI::Events::PLAYER_POWER_UP_RECHARGED, _powerUpType);
          },
          cooldownDuration);
    }

    ~PowerUpCharge() {
      durationTimer->Cancel();
      cooldownTimer->Cancel();
    }

    bool IsOnCooldown() const { return _onCooldown; };

    bool Use() {
      if (!IsOnCooldown()) {
        _onCooldown = true;
        EmitUserEvent(UCI::Events::PLAYER_POWER_UP_GAINED, _powerUpType);
        durationTimer->Start();
        cooldownTimer->Start();
        return true;
      }
      return false;
    }

    void Pause() {
      durationTimer->Pause();
      cooldownTimer->Pause();
    }

    void Resume() {
      durationTimer->Unpause();
      cooldownTimer->Unpause();
    }

    private:
    std::atomic<bool> _onCooldown;
    PowerUp::PowerUpType _powerUpType;
    Scope<CoffeeMaker::Async::TimeoutTask> cooldownTimer;
    Scope<CoffeeMaker::Async::TimeoutTask> durationTimer;
  };

  class PowerMissle;
  class MineBomb;
  class ForceShield;

  class Warp : public PowerUp, CoffeeMaker::IUserEventListener {
    public:
    Warp() {
      _enabledSoundEffect = CreateScope<CoffeeMaker::AudioElement>("effects/Warp.ogg");
      _charges.push_back(new PowerUpCharge(PowerUp::PowerUpType::Warp, 250, 5000));
      _charges.push_back(new PowerUpCharge(PowerUp::PowerUpType::Warp, 250, 5000));
      _charges.push_back(new PowerUpCharge(PowerUp::PowerUpType::Warp, 250, 5000));
    }

    virtual void Use() {
      for (size_t i = 0; i < _charges.size(); i++) {
        if (_charges[i]->Use()) {
          _enabledSoundEffect->Play();
          break;
        }
      }
    }

    virtual void OnSDLUserEvent(const SDL_UserEvent& event) {
      if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_PAUSE) {
        for (size_t i = 0; i < _charges.size(); i++) {
          _charges[i]->Pause();
        }
        return;
      }

      if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_GAME_UNPAUSE) {
        for (size_t i = 0; i < _charges.size(); i++) {
          _charges[i]->Resume();
        }
        return;
      }

      if (event.code == CoffeeMaker::ApplicationEvents::COFFEEMAKER_SCENE_UNLOAD) {
        for (size_t i = 0; i < _charges.size(); i++) {
          delete _charges[i];
        }
        return;
      }

      if (event.type == UCI::Events::PLAYER_POWER_UP_RECHARGED && event.code == PowerUpType::Warp) {
        CoffeeMaker::Logger::Debug("[PLAYER_EVENT][PLAYER_POWER_UP_RECHARGED][WARP]");
        return;
      }
    }

    private:
    std::vector<PowerUpCharge*> _charges;
  };
}  // namespace UCI

#endif
