#ifndef _coffeemaker_messagebox_hpp
#define _coffeemaker_messagebox_hpp

#include <string>

namespace CoffeeMaker {

class MessageBox {
 public:
  /**
   * Shows a simple message box with a give title and message, upon close of the
   * message box, and SDL_QUIT event will be pushed into the message loop and
   * the program will exit.
   */
  static void ShowMessageBoxAndQuit(const std::string& title,
                                    const std::string& message);

 private:
  MessageBox();
};

}  // namespace CoffeeMaker

#endif
