#ifndef _basepowerup_hpp
#define _basepowerup_hpp

#include <atomic>
#include <string>

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
    virtual ~PowerUp() = default;

    virtual void Use() = 0;

    protected:
    Scope<CoffeeMaker::AudioElement> _enabledSoundEffect;
    Scope<CoffeeMaker::AudioElement> _disabledSoundEffect;
  };

  class PowerUpCharge : public CoffeeMaker::UserEventEmitter {
    public:
    PowerUpCharge(PowerUp::PowerUpType type, int enabledDuration, int cooldownDuration) :
        _onCooldown(false), _powerUpType(type) {
      durationTimer = CreateScope<CoffeeMaker::Async::TimeoutTask>(
          "PowerUpEnabled", [this] { EmitUserEvent(UCI::Events::PLAYER_POWER_UP_LOST, _powerUpType); },
          enabledDuration);
      cooldownTimer = CreateScope<CoffeeMaker::Async::TimeoutTask>(
          "PowerUpCooldown",
          [this] {
            _onCooldown = false;
            EmitUserEvent(UCI::Events::PLAYER_POWER_UP_RECHARGED, _powerUpType);
          },
          cooldownDuration);
    }

    ~PowerUpCharge() = default;

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
    Scope<CoffeeMaker::Async::TimeoutTask> durationTimer;
    Scope<CoffeeMaker::Async::TimeoutTask> cooldownTimer;
  };

  class PowerMissle;
  class MineBomb;
  class ForceShield;

  class Warp : public PowerUp, CoffeeMaker::IUserEventListener {
    public:
    Warp() {
      _enabledSoundEffect = CreateScope<CoffeeMaker::AudioElement>(soundFileName);
      _charges.push_back(new PowerUpCharge(PowerUp::PowerUpType::Warp, enabledDuration, cooldownDuration));
      _charges.push_back(new PowerUpCharge(PowerUp::PowerUpType::Warp, enabledDuration, cooldownDuration));
      _charges.push_back(new PowerUpCharge(PowerUp::PowerUpType::Warp, enabledDuration, cooldownDuration));
    }

    void Use() override {
      for (size_t i = 0; i < _charges.size(); i++) {
        if (_charges[i]->Use()) {
          _enabledSoundEffect->Play();
          break;
        }
      }
    }

    void OnSDLUserEvent(const SDL_UserEvent& event) override {
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
    static constexpr int enabledDuration = 250;
    static constexpr int cooldownDuration = 5000;
    static const std::string soundFileName;
  };
}  // namespace UCI

#endif
