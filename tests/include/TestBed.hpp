#ifndef _coffeemaker_testbed_hpp
#define _cofeemaker_testbed_hpp

#include "Window.hpp"
#include "Renderer.hpp"

namespace CoffeeMaker
{
  namespace Test
  {

    class TestBed
    {
    public:
      TestBed();
      ~TestBed();

      void Reset();
      void ClearScreen();
      void BeginRender();
      void EndRender();

    protected:
      CoffeeMaker::IWindow *_window;
      CoffeeMaker::Renderer *_renderer;
    };

  } // namespace Test
} // namespace CoffeeMaker

#endif
