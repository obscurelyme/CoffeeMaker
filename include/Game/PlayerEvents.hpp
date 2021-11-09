#include <memory>

#include "Event.hpp"

extern std::unique_ptr<CoffeeMaker::Event> incScore;
extern std::unique_ptr<CoffeeMaker::Event> decLife;

enum GameEvents {
  PLAYER_LOST_LIFE = 9000,
  PLAYER_INCREMENT_SCORE,
  ENEMY_INITIAL_INTERVAL_SPAWN,
  SHOW_MENU,
  HEADS_UP_DISPLAY_INCREMENT_TIMER
};
