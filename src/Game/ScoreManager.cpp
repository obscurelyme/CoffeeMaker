#include "Game/ScoreManager.hpp"

#include <iostream>
#include <sstream>
#include <string>

#include "Coroutine.hpp"
#include "File.hpp"
#include "Game/Events.hpp"
#include "Logger.hpp"

ScoreManager* ScoreManager::_instance = nullptr;
unsigned int ScoreManager::_incrementAmount = 10;

ScoreManager::ScoreManager() :
    _score(0),
    _highScores(HighScores{.firstPlace = 0, .secondPlace = 0, .thirdPlace = 0}),
    _scoreFile(CoffeeMaker::File{.name = "scores.txt", .loaded = false, .data = nullptr}) {}

ScoreManager::~ScoreManager() { _instance = nullptr; }

void ScoreManager::Init() {
  if (_instance == nullptr) {
    _instance = new ScoreManager();
    _instance->LoadScores();
  }
}

CoffeeMaker::Coroutine ScoreManager::LoadScores() { _scoreFile = co_await CoffeeMaker::ReadFileAwaiter("scores.txt"); }

CoffeeMaker::Coroutine ScoreManager::SaveScores() {
  std::stringstream scoreStr;
  scoreStr << std::to_string(_highScores.firstPlace) << "|";
  scoreStr << std::to_string(_highScores.secondPlace) << "|";
  scoreStr << std::to_string(_highScores.thirdPlace);

  co_await CoffeeMaker::WriteFileAwaiter("scores.txt", scoreStr.str());
}

void ScoreManager::ResetScore() { _instance->_score = 0; }

void ScoreManager::Destroy() {
  delete _instance;
  _instance = nullptr;
}

void ScoreManager::LoadHighScores() {
  if (_instance->_scoreFile.loaded) {
    std::string scoreStr = _instance->_scoreFile.data;
    std::string delimiter = "|";
    size_t pos = 0;
    std::string token = "|";

    try {
      // first place
      pos = scoreStr.find(delimiter);
      token = scoreStr.substr(0, pos);
      _instance->_highScores.firstPlace = std::stoi(token);
      scoreStr.erase(0, pos + delimiter.length());
      // second place
      pos = scoreStr.find(delimiter);
      token = scoreStr.substr(0, pos);
      _instance->_highScores.secondPlace = std::stoi(token);
      scoreStr.erase(0, pos + delimiter.length());
      // third place
      _instance->_highScores.thirdPlace = std::stoi(scoreStr);
      scoreStr.erase(0, pos + delimiter.length());
    } catch (const std::exception& e) {
      std::cout << e.what() << std::endl;
      // no saved high scores...
    }
  }
}

void ScoreManager::SaveHighScores() { _instance->SaveScores(); }

HighScores ScoreManager::GetHighScores() { return _instance->_highScores; }

int ScoreManager::CurrentScorePlacement() {
  if (_instance->_score >= _instance->_highScores.firstPlace) {
    return 1;
  }
  if (_instance->_score >= _instance->_highScores.secondPlace) {
    return 2;
  }
  if (_instance->_score >= _instance->_highScores.thirdPlace) {
    return 3;
  }
  return -1;
}

void ScoreManager::IncrementScore(unsigned int pointsToAdd) { _instance->_score += pointsToAdd; }

unsigned int ScoreManager::GetScore() { return _instance->_score; }

void ScoreManager::OnSDLUserEvent(const SDL_UserEvent& event) {
  if (event.type == UCI::Events::PLAYER_INCREMENT_SCORE) {
    if (event.code == Multiplier::Super) {
      _score += _incrementAmount * Multiplier::Super;
      return;
    }
    if (event.code == Multiplier::Extreme) {
      _score += _incrementAmount * Multiplier::Extreme;
      return;
    }
    _score += _incrementAmount;
  }
}
