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
#include "Utilities.hpp"
#include "Widgets/UIComponent.hpp"

namespace CoffeeMaker {
  enum class ButtonType { Textured, Standard };

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
    /**
     * Constructs a button that will use the provided colors
     */
    Button(const SDL_Color &defaultColor, const SDL_Color &hoveredColor, Uint32 width, Uint32 height);
    /**
     * Constructs a button that will display a default Texture and a hover Texture when appropriate
     */
    Button(const std::string &defaultTexture, const std::string &hoveredTexture);
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

    void SetWidth(Uint32 width);
    void SetHeight(Uint32 height);

    void OnMouseover();
    void OnMouseleave();
    void OnMouseUp(const Event &e);
    void OnMouseDown(const Event &e);
    void OnMouseMotion(const Event &e);

    void Render() override;
    std::string ID() const override;

    static void PollEvents(const SDL_Event *const event);
    static void ProcessEvents();

    // int top;
    // int left;
    // int width;
    // int height;
    // int padding;
    void *children;
    // Texture _texture;
    // SDL_Color _textureColorMod;

    Ref<Texture> _currentTexture;
    Ref<Texture> _defaultTexture;
    Ref<Texture> _hoveredTexture;
    SDL_Color _defaultColor;
    SDL_Color _hoveredColor;
    SDL_Color _currentColor;

    std::map<ButtonEventType, Event *> _events;

    static std::map<std::string, Button *> buttons;
    static std::queue<Event *> eventQueue;
    static int _buttonUid;

    private:
    // Emplaces the newly created button in the static vector of buttons
    void _EmplaceButton();
    void _AttachDefaultEvents();
    bool _HitDetection(const int &mouseX, const int &mouseY);
    bool _hovered;
    std::string _componentId;
    ButtonType _type;
  };

}  // namespace CoffeeMaker

#endif
