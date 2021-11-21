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
  class UserEventHandler;
  class MouseEventHandler;

  /**
   * @brief Interface that provides an easy way for any class to be able
   * to handle SDL_MouseMotionEvents, SDL_MouseButtonEvents, and
   * SDL_MouseWheelEvents. Provides a few virtual functions for
   * the derived class to implement...
   *
   * `OnMouseDown`
   * `OnMouseUp`
   * `OnMouseMove`
   * `OnMouseWheel`
   */
  class IMouseListener {
    protected:
    IMouseListener();

    public:
    virtual ~IMouseListener();
    virtual void OnMouseDown(const SDL_MouseButtonEvent& event) = 0;
    virtual void OnMouseUp(const SDL_MouseButtonEvent& event) = 0;
    virtual void OnMouseMove(const SDL_MouseMotionEvent& event) = 0;
    virtual void OnMouseWheel(const SDL_MouseWheelEvent& event) = 0;

    friend MouseEventHandler;

    private:
    unsigned int _id;
    bool _live;
    static unsigned int _uid;
    // NOTE: upon creation, instances are not live until the next frame.
    // after which they become listeners.
    static std::vector<IMouseListener*> _instances;

    static std::vector<IMouseListener*> _listeners;
    static void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& event);
    static void ProcessMouseButtonEvent(const SDL_MouseButtonEvent& event);
    static void ProcessMouseWheelEvent(const SDL_MouseWheelEvent& event);
  };

  class MouseEventHandler {
    public:
    static void HandleMouseEvents(const SDL_Event& event);
    static void AddNewMouseHandlers();
  };

  /**
   * @brief Interface that provides an easy way for any class to be able
   * to handle SDL_UserEvents. Provides a single virtual function for
   * the derived class to implement, `OnSDLUserEvent`
   */
  class IUserEventListener {
    protected:
    IUserEventListener();

    public:
    virtual ~IUserEventListener();
    virtual void OnSDLUserEvent(const SDL_UserEvent& event) = 0;

    friend class UserEventHandler;

    private:
    unsigned int _id;
    static unsigned int _uid;
    static std::vector<IUserEventListener*> _listeners;
    static void ProcessUserEvent(const SDL_UserEvent& event);
  };

  /**
   * @brief Core handler for all SDL_UserEvents
   */
  class UserEventHandler {
    public:
    static void HandleUserEvent(const SDL_UserEvent& event) {
      CoffeeMaker::IUserEventListener::ProcessUserEvent(event);
    }
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

  /**
   * Constructs an SDL_USEREVENT based on the enum and pushes it
   * into the SDL_Event queue.
   */
  void PushCoffeeMakerEvent(ApplicationEvents appEvent);

  /**
   * Constructs an SDL_USEREVENT based on the enum and pushes it
   * into the SDL_Event queue.
   */
  void PushEvent(Sint32 eventCode, void* data1 = nullptr, void* data2 = nullptr);

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
