#ifndef _game_events_hpp
#define _game_events_hpp

namespace UCI {
  enum Events {
    INIT = 9000,
    // Player Events ////////////////////////////////////////////////////////////
    PLAYER_LOST_LIFE,
    PLAYER_INCREMENT_SCORE,
    PLAYER_BEGIN_SPAWN,
    PLAYER_COMPLETE_SPAWN,
    PLAYER_POWER_UP_GAINED_IMMUNITY,
    PLAYER_POWER_UP_LOST_IMMUNITY,
    PLAYER_DESTROYED,
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
    HEADS_UP_DISPLAY_INCREMENT_TIMER
  };
}

#endif
