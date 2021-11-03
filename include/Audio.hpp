#ifndef _coffeemaker_audio_hpp
#define _coffeemaker_audio_hpp

#include <SDL2/SDL_mixer.h>

#include <string>

namespace CoffeeMaker {

  class Audio {
    public:
    static void Init();
    static void Quit();
    static Mix_Music* LoadMusic(const std::string& filename);
    static void FreeMusic(Mix_Music* music);
    static void PlayMusic(Mix_Music* music);
    static void StopMusic();
  };

}  // namespace CoffeeMaker

#endif
