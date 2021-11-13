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

  int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
  int initializedFlags = Mix_Init(flags);
  if ((initializedFlags & flags) != flags) {
    std::string msg = fmt::format(fmt::runtime("Could not initialize SDL Mixer {}"), Mix_GetError());
    CM_LOGGER_CRITICAL(msg);
    CoffeeMaker::MessageBox::ShowMessageBoxAndQuit("CoffeeMaker::Audio Error", msg);
  }
}

void CoffeeMaker::Audio::Quit() { Mix_CloseAudio(); }

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
    CM_LOGGER_INFO("Current Volume {}", Mix_VolumeMusic(1));
  }
}

void CoffeeMaker::Audio::StopMusic() { Mix_HaltMusic(); }

CoffeeMaker::AudioElement::AudioElement(const std::string& filePath) : _chunk(nullptr), _channel(-1) {
  std::string fp =
      fmt::format(fmt::runtime("{}/audio/{}"), CoffeeMaker::Utilities::AssetsDirectory(), filePath.c_str());
  _chunk = Mix_LoadWAV(fp.c_str());
  if (_chunk == nullptr) {
    CM_LOGGER_CRITICAL("Could not load sound file for AudioElement {}", fp);
  }
}

CoffeeMaker::AudioElement::~AudioElement() {
  if (_chunk != nullptr) {
    Mix_FreeChunk(_chunk);
    _chunk = nullptr;
  }
}

void CoffeeMaker::AudioElement::Play() {
  if (_chunk != nullptr) {
    if (Mix_Playing(_channel)) {
      Mix_PlayChannel(-1, _chunk, 0);
    }
    Mix_VolumeChunk(_chunk, 1);
    _channel = Mix_PlayChannel(_channel, _chunk, 0);
  }
}

void CoffeeMaker::AudioElement::Stop() {
  if (_chunk != nullptr) {
    Mix_HaltChannel(_channel);
  }
}
