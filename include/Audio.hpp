#ifndef _coffeemaker_audio_hpp
#define _coffeemaker_audio_hpp

#include <SDL2/SDL_mixer.h>

#include <string>

// #include "Utilities.hpp"

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

  class AudioElement {
    public:
    explicit AudioElement(const std::string& filePath);
    ~AudioElement();

    void Play();
    void Stop();

    Mix_Chunk* _chunk;
    int _channel;
  };

}  // namespace CoffeeMaker

#endif
