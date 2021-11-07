#ifndef _coffeemaker_event_hpp
#define _coffeemaker_event_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <vector>

namespace CoffeeMaker {
  class Event;
  class GameEvent;

  /**
   * @brief Simple class to assign and hold functions to be
   * invoked at a later time.
   */
  class Delegate2 {
    public:
    explicit Delegate2(std::function<void(const GameEvent& event)> fn) : _function(fn), _id(++_uid){};
    ~Delegate2() { _function = nullptr; }

    inline void Invoke(const GameEvent& event) { _function(event); }
    inline std::function<void(const GameEvent& event)> Get() { return _function; }
    inline bool operator==(const Delegate2& rhs) const { return _id == rhs._id; }

    private:
    std::function<void(const GameEvent& event)> _function;
    int _id;

    static int _uid;
  };

  /**
   * Generic Application level events
   */
  enum ApplicationEvents {
    COFFEEMAKER_GAME_PAUSE,
    COFFEEMAKER_GAME_UNPAUSE,
    COFFEEMAKER_GAME_QUIT,
    COFFEEMAKER_SCENE_LOAD,
    COFFEEMAKER_SCENE_UNLOAD,
    COFFEEMAKER_SCENE_EVENT
  };

  class GameEvents {
    public:
    static std::map<Sint32, GameEvent*> Events2;
    static std::map<std::string, int> Events;
    static Sint32 Marker;

    static void AddEvent(Sint32 name);
    static void AddEvent(const std::string& name);
    static void PushEvent(Sint32 code = 0, void* data1 = nullptr, void* data2 = nullptr);
    static void PushEvent(const std::string& name, Sint32 code = 0, void* data1 = nullptr, void* data2 = nullptr);
    static void ProcessEvent(const SDL_UserEvent& event);
  };

  class GameEvent {
    public:
    explicit GameEvent(Sint32 code) : _code(code), _listeners({}) { GameEvents::Events2.emplace(_code, this); }
    ~GameEvent() { RemoveAllListeners(); }

    void AddListener(Delegate2 listener) { _listeners.push_back(listener); };
    void RemoveListener(Delegate2 listener) {
      for (auto it = _listeners.begin(); it != _listeners.end();) {
        if (listener == *it) {
          it = _listeners.erase(it);
          break;
        } else {
          ++it;
        }
      }
    };
    void RemoveAllListeners() { _listeners.clear(); };

    void Emit(void* data1, void* data2) {
      for (auto listener : _listeners) {
        listener.Invoke(*this);
      }
    };

    private:
    std::vector<Delegate2> _listeners;
    Sint32 _code;
  };

  /**
   * Constructs an SDL_USEREVENT based on the enum and pushes it
   * into the SDL_Event queue.
   */
  void PushCoffeeMakerEvent(ApplicationEvents appEvent);

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
