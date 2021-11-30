#ifndef _coffeemaker_sdl_mouse_events_hpp
#define _coffeemaker_sdl_mouse_events_hpp

#include <SDL2/SDL.h>

#include <vector>

namespace CoffeeMaker {
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

    bool IsActive() const { return _active; }

    friend MouseEventHandler;

    private:
    bool _active;
    unsigned int _id;
    // size_t _index;
    static unsigned int _uid;

    static std::vector<IMouseListener*> _listeners;
    static void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& event);
    static void ProcessMouseButtonEvent(const SDL_MouseButtonEvent& event);
    static void ProcessMouseWheelEvent(const SDL_MouseWheelEvent& event);
    static void RemoveStaleListeners();
  };

  class MouseEventHandler {
    public:
    static void HandleMouseEvents(const SDL_Event& event);
    static void ClearMouseEvents();
  };
}  // namespace CoffeeMaker

#endif
