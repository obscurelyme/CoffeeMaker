#ifndef _coffeemaker_button_hpp
#define _coffeemaker_button_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <map>
#include <queue>
#include <string>

#include "Color.hpp"
#include "Event.hpp"
#include "Texture.hpp"
#include "Widgets/UIComponent.hpp"

namespace CoffeeMaker {

  class Button : public UIComponent {
    public:
    enum class ButtonEventType {
      OnClick,
      MouseIn,
      MouseOut,
      MouseMotion = SDL_MOUSEMOTION,
      MouseDown = SDL_MOUSEBUTTONDOWN,
      MouseUp = SDL_MOUSEBUTTONUP
    };

    public:
    Button();
    ~Button();

    /**
     * Add an event listener to the button
     */
    inline void On(ButtonEventType type, Delegate delegate) {
      auto e = _events.find(type);
      if (e == _events.end()) {
        _events.emplace(type, new Event());
      }
      _events.at(type)->AddListener(delegate);
    }
    /**
     * Removes an event listener from the button
     */
    inline void Off(ButtonEventType type, Delegate delegate) { _events.at(type)->RemoveListener(delegate); }

    void SetBackgroundColor(const SDL_Color &color);
    void SetTexture(const Texture &texture);
    void SetTexture(const std::string &filePath);

    void OnEvent(const SDL_Event *e);
    void OnMouseover();
    void OnClick();
    void OnMouseleave();
    void OnMouseUp(const Event &e);
    void OnMouseDown(const Event &e);
    void OnMouseMotion(const Event &e);

    void Render();

    static void PollEvents(const SDL_Event *const event);
    static void ProcessEvents();

    int top;
    int left;
    int width;
    int height;
    int padding;
    void *children;
    Texture _texture;
    std::function<void()> onClickCallback;
    SDL_Color _textureColorMod;

    std::map<ButtonEventType, Event *> _events;

    static std::map<std::string, Button *> buttons;
    static std::queue<std::function<void()>> onClickCallbacks;
    static std::queue<Event *> eventQueue;
    static int _buttonUid;

    private:
    bool _HitDetection(const int &mouseX, const int &mouseY);
    // int index;
    bool _hovered;
    std::string _componentId;
  };

}  // namespace CoffeeMaker

#endif
