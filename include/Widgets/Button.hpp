#ifndef _coffeemaker_button_hpp
#define _coffeemaker_button_hpp

#include <SDL2/SDL.h>

#include <functional>
#include <map>
#include <queue>
#include <string>

#include "Color.hpp"
#include "Texture.hpp"
#include "Widgets/UIComponent.hpp"

namespace CoffeeMaker {

  class Button : public UIComponent {
    public:
    Button();
    ~Button();

    void SetBackgroundColor(const SDL_Color &color);
    void SetTexture(const Texture &texture);
    void SetTexture(const std::string &filePath);

    void OnEvent(const SDL_Event *e);
    void OnMouseover();
    void OnClick();
    void OnMouseleave();

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

    static std::map<std::string, Button *> buttons;
    static std::queue<std::function<void()>> onClickCallbacks;

    private:
    bool _HitDetection(const int &mouseX, const int &mouseY);
    int index;
    bool _hovered;
  };

}  // namespace CoffeeMaker

#endif
