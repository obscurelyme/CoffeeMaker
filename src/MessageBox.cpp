#include "MessageBox.hpp"
#include <SDL2/SDL.h>

using namespace CoffeeMaker;

void MessageBox::ShowMessageBoxAndQuit(const std::string& title, const std::string& message) {
  SDL_Event quitEvent;
  quitEvent.type = SDL_QUIT;
  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
  SDL_PushEvent(&quitEvent);
}
