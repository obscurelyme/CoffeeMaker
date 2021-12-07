#ifndef _coffeemaker_event_hpp
#define _coffeemaker_event_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <vector>

#include "Events/MouseEvents.hpp"
#include "Events/UserEvents.hpp"

namespace CoffeeMaker {
  class Event;

  /**
   * Generic Application level events
   */
  enum ApplicationEvents {
    COFFEEMAKER_GAME_PAUSE,
    COFFEEMAKER_GAME_UNPAUSE,
    COFFEEMAKER_GAME_QUIT,
    COFFEEMAKER_SCENE_LOAD,
    COFFEEMAKER_SCENE_UNLOAD,
    COFFEEMAKER_SCENE_EVENT,
    COFFEEMAKER_FILE_WRITTEN,
    COFFEEMAKER_FILE_READ
  };

  /**
   * Constructs an SDL_USEREVENT based on the enum and pushes it
   * into the SDL_Event queue.
   */
  void PushCoffeeMakerEvent(ApplicationEvents appEvent);

  /**
   * Constructs an SDL_USEREVENT based on the code enum and pushes it
   * into the SDL_Event queue.
   */
  void PushEvent(Sint32 eventCode, void* data1 = nullptr, void* data2 = nullptr);

  /**
   * Constructs an SDL_USEREVENT based on the type enum and pushes it
   * into the SDL_Event queue.
   */
  void PushUserEvent(Uint32 type, Sint32 eventCode = -1, void* data1 = nullptr, void* data2 = nullptr);

  class UserEventEmitter {
    protected:
    UserEventEmitter() {}
    ~UserEventEmitter() = default;

    /**
     * @brief Alias for CoffeeMaker::PushUserEvent
     *
     * @param type
     * @param eventCode
     * @param data1
     * @param data2
     */
    void EmitUserEvent(Uint32 type, Sint32 eventCode = -1, void* data1 = nullptr, void* data2 = nullptr) {
      CoffeeMaker::PushUserEvent(type, eventCode, data1, data2);
    }
  };

  class Delegate {
    public:
    explicit Delegate(std::function<void(const Event& event)> fn);
    // explicit Delegate(std::function<void(const SDL_Event& event)> fn);
    ~Delegate();

    inline void Invoke(const Event& event) { _function(event); }
    inline std::function<void(const Event& event)> Get() { return _function; }
    inline bool operator==(const Delegate& rhs) const { return _id == rhs._id; }

    private:
    std::function<void(const Event& event)> _function;
    int _id;

    static int _uid;
  };

  using EventListener = Delegate;
  using EventListeners = std::vector<EventListener>;
  using EventList = std::list<EventListener>;

  class Event {
    public:
    ~Event();
    void Emit();
    void AddListener(EventListener listener);
    void RemoveListener(EventListener listener);
    void RemoveAllListeners();

    private:
    EventListeners _listeners;
    EventList _list;
  };

}  // namespace CoffeeMaker

#endif
