#ifndef _coffeemaker_file_hpp
#define _coffeemaker_file_hpp

#include <string>

namespace CoffeeMaker {

  struct File {
    std::string name;
    bool loaded;
    char* data;
  };

}  // namespace CoffeeMaker

#endif
