#ifndef _coffeemaker_sdl_user_events_hpp
#define _coffeemaker_sdl_user_events_hpp

#include <SDL2/SDL.h>

#include <vector>

namespace CoffeeMaker {
  class UserEventHandler;

  /**
   * @brief Interface that provides an easy way for any class to be able
   * to handle SDL_UserEvents. Provides a single virtual function for
   * the derived class to implement, `OnSDLUserEvent`
   */
  class IUserEventListener {
    protected:
    IUserEventListener();
    virtual ~IUserEventListener();

    public:
    virtual void OnSDLUserEvent(const SDL_UserEvent& event) = 0;

    static size_t NumListeners() { return _listeners.size(); }

    friend class UserEventHandler;

    private:
    unsigned int _id;
    unsigned int _index;
    static unsigned int _uid;
    static std::vector<IUserEventListener*> _listeners;
    static void ProcessUserEvent(const SDL_UserEvent& event);
    static void RemoveStaleListeners();
  };

  /**
   * @brief Core handler for all SDL_UserEvents
   */
  class UserEventHandler {
    public:
    static void HandleUserEvent(const SDL_UserEvent& event) {
      CoffeeMaker::IUserEventListener::ProcessUserEvent(event);
      ClearUserEvents();
    }
    static void ClearUserEvents() { CoffeeMaker::IUserEventListener::RemoveStaleListeners(); }
  };

}  // namespace CoffeeMaker

#endif
