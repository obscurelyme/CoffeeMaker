#include "Game/ScoreManager.hpp"

#include "Coroutine.hpp"
#include "File.hpp"
#include "Game/Events.hpp"
#include "Logger.hpp"

ScoreManager* ScoreManager::_instance = nullptr;
unsigned int ScoreManager::_incrementAmount = 10;

ScoreManager::ScoreManager() : _score(0), _highScores(HighScores{.firstPlace = 0, .secondPlace = 0, .thirdPlace = 0}) {}

ScoreManager::~ScoreManager() { _instance = nullptr; }

void ScoreManager::Init() {
  if (_instance == nullptr) {
    _instance = new ScoreManager();
    _instance->LoadScores();
  }
}

CoffeeMaker::Coroutine ScoreManager::LoadScores() { _scoreFile = co_await CoffeeMaker::ReadFileAwaiter("scores.txt"); }

void ScoreManager::ResetScore() { _instance->_score = 0; }

void ScoreManager::Destroy() {
  delete _instance;
  _instance = nullptr;
}

void ScoreManager::LoadHighScores() {
  // TODO(obscurelyme) this will eventually need to pull in high scores from a local file.
  _instance->_highScores = HighScores{.firstPlace = 5000, .secondPlace = 2500, .thirdPlace = 1000};
}

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
