#ifndef _coffeemaker_component_hpp
#define _coffeemaker_component_hpp

#include <SDL2/SDL.h>

#include <memory>
#include <string>
#include <vector>

#include "Properties.hpp"

namespace CoffeeMaker {

  struct Margins {
    float top;
    float bottom;
    float left;
    float right;
  };

  class UIComponent {
    public:
    UIComponent();
    explicit UIComponent(const SDL_Rect& clientRect);
    virtual ~UIComponent();

    /**
     * Toggle the rendering of the clientRect for the component
     */
    static void SetDebugRender(bool toggle);
    virtual void AppendChild(const std::shared_ptr<UIComponent>& component);
    /**
     * Function that is executed upon becoming a child.
     */
    virtual void OnAppend();
    virtual void Render();
    /**
     * Returns the ID of the component
     */
    virtual std::string ID() const;
    void SetHorizontalAlignment(CoffeeMaker::UIProperties::HorizontalAlignment xAlign);
    void SetVerticalAlignment(CoffeeMaker::UIProperties::VerticalAlignment yAlign);
    void SetMargins(const Margins& margins);

    SDL_Rect viewport;
    SDL_Rect clientRect;

    protected:
    void CalcPosition();
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

    protected:
    float _marginTop;
    float _marginBottom;
    float _marginLeft;
    float _marginRight;
  };
}  // namespace CoffeeMaker

#endif
