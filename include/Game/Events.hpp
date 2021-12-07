#ifndef _game_events_hpp
#define _game_events_hpp

#include <SDL2/SDL.h>

namespace UCI {
  enum Events {
    FIRST_EVENT = SDL_USEREVENT,

    INIT,
    // Player Events ////////////////////////////////////////////////////////////
    PLAYER_LOST_LIFE,
    PLAYER_INCREMENT_SCORE,
    PLAYER_BEGIN_SPAWN,
    PLAYER_COMPLETE_SPAWN,
    PLAYER_POWER_UP_GAINED_IMMUNITY,
    PLAYER_POWER_UP_LOST_IMMUNITY,
    PLAYER_DESTROYED,
    PLAYER_FIRE_DELAY_START,
    PLAYER_FIRE_DELAY_END,
    PLAYER_LOST_GAME,
    // Player Power up Events //////////////////////////////////////////////////
    PLAYER_POWER_UP_GAINED,
    PLAYER_POWER_UP_USED,
    PLAYER_POWER_UP_LOST,
    PLAYER_POWER_UP_RECHARGED,
    // Enemy Events ////////////////////////////////////////////////////////////
    ENEMY_INITIAL_INTERVAL_SPAWN,
    ENEMY_DESTROYED,
    ENEMY_SPAWNED,
    ENEMY_BEGIN_SPAWN,
    ENEMY_COMPLETE_SPAWN,
    ENEMY_FIRE_MISSILE,
    ENEMY_BEGIN_EXIT,
    ENEMY_COMPLETE_EXIT,
    // User Interface Events ///////////////////////////////////////////////////
    SHOW_MENU,
    HEADS_UP_DISPLAY_INCREMENT_TIMER,
    // Level Events ////////////////////////////////////////////////////////////
    LOAD_NEW_SCENE,

    LAST_EVENT
  };

  int NumEventsToRegister();
}  // namespace UCI

#endif
