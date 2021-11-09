#ifndef _game_events_hpp
#define _game_events_hpp

namespace UCI {
  enum Events {
    INIT = 9000,
    PLAYER_LOST_LIFE,
    PLAYER_INCREMENT_SCORE,
    ENEMY_INITIAL_INTERVAL_SPAWN,
    SHOW_MENU,
    HEADS_UP_DISPLAY_INCREMENT_TIMER
  };
}

#endif
