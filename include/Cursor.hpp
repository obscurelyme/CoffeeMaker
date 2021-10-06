#ifndef _coffeemaker_cursor_hpp
#define _coffeemaker_cursor_hpp

#include <SDL2/SDL.h>

#include <string>

namespace CoffeeMaker {

  class Cursor {
    public:
    explicit Cursor(const std::string& filePath);
    ~Cursor();

    private:
    SDL_Cursor* _cursor;
  };

}  // namespace CoffeeMaker

#endif
