#ifndef _coffeemaker_component_hpp
#define _coffeemaker_component_hpp

#include <SDL2/SDL.h>

#include <memory>
#include <string>
#include <vector>

#include "Properties.hpp"

namespace CoffeeMaker {
  class UIComponent {
    public:
    UIComponent();
    UIComponent(const SDL_Rect clientRect);
    virtual ~UIComponent();

    /**
     * Toggle the rendering of the clientRect for the component
     */
    static void SetDebugRender(bool toggle);
    void AppendChild(const std::shared_ptr<UIComponent>& component);
    virtual void Render();
    void SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment xAlign);
    void SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment yAlign);

    SDL_Rect viewport;
    SDL_Rect clientRect;

    protected:
    int DeriveXPosition();
    int DeriveYPosition();
    void RepositionChildren();
    void DebugRender();

    std::vector<std::shared_ptr<UIComponent>> _children;
    UIComponent* _parent;
    CoffeeMaker::UIProperties::HorizontalAlignment _xAlign;
    CoffeeMaker::UIProperties::VerticalAlignment _yAlign;
    std::string _id;

    private:
    static bool _debugRendering;
    static int _uid;
  };
}  // namespace CoffeeMaker

#endif
