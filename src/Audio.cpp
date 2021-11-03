#include "Audio.hpp"

#include <fmt/core.h>

#include "Logger.hpp"
#include "MessageBox.hpp"
#include "Utilities.hpp"

void CoffeeMaker::Audio::Init() {
  CM_LOGGER_INFO("Mixer Version: {}", SDL_MIXER_COMPILEDVERSION);
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    std::string msg = fmt::format(fmt::runtime("Could not Open Audio {}"), Mix_GetError());
    CM_LOGGER_CRITICAL(msg);
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("CoffeeMaker::Audio Error", msg);
    return;
  }

  int flags = MIX_INIT_MP3;
  int initializedFlags = Mix_Init(flags);
  if ((initializedFlags & flags) != flags) {
    std::string msg = fmt::format(fmt::runtime("Could not initialize SDL Mixer {}"), Mix_GetError());
    CM_LOGGER_CRITICAL(msg);
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("CoffeeMaker::Audio Error", msg);
  }
}

void CoffeeMaker::Audio::Quit() {
  Mix_Quit();
  Mix_CloseAudio();
}

Mix_Music* CoffeeMaker::Audio::LoadMusic(const std::string& filename) {
  std::string fullFilePath =
      fmt::format(fmt::runtime("{}/audio/{}"), CoffeeMaker::Utilities::AssetsDirectory(), filename.c_str());

  Mix_Music* music = Mix_LoadMUS(fullFilePath.c_str());
  if (!music) {
    CM_LOGGER_CRITICAL("Could not load music file: {}", Mix_GetError());
  }

  return music;
}

void CoffeeMaker::Audio::FreeMusic(Mix_Music* music) {
  if (music != nullptr) {
    Mix_FreeMusic(music);
  }
}

void CoffeeMaker::Audio::PlayMusic(Mix_Music* music) {
  if (music != nullptr) {
    Mix_PlayMusic(music, -1);
  }
}

void CoffeeMaker::Audio::StopMusic() { Mix_HaltMusic(); }
