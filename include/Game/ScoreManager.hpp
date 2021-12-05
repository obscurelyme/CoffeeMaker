#ifndef _game_score_hpp
#define _game_score_hpp

#include "Coroutine.hpp"
#include "Event.hpp"
#include "File.hpp"
#include "Utilities.hpp"

struct HighScores {
  unsigned int firstPlace;
  unsigned int secondPlace;
  unsigned int thirdPlace;
};

class ScoreManager : public CoffeeMaker::IUserEventListener {
  public:
  enum Multiplier { Standard = -1, Super = 2, Extreme = 5 };

  static void Init();
  static void LoadHighScores();
  static int CurrentScorePlacement();
  static void Destroy();
  static void IncrementScore(unsigned int pointsToAdd);
  static unsigned int GetScore();
  static void ResetScore();

  void OnSDLUserEvent(const SDL_UserEvent& event) override;

  protected:
  ScoreManager();
  ~ScoreManager();
  CoffeeMaker::Coroutine LoadScores();

  private:
  static ScoreManager* _instance;
  static unsigned int _incrementAmount;
  CoffeeMaker::File _scoreFile;

  unsigned int _score;
  HighScores _highScores;
};

#endif
