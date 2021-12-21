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
  enum Multiplier { Standard = -1, Super = 3, Ultra = 5, Extreme = 10, Flagship = 50 };

  static void Init();
  static void LoadHighScores();
  static void SaveHighScores();
  static HighScores GetHighScores();
  static int CurrentScorePlacement();
  static void Destroy();
  static void IncrementScore(unsigned int pointsToAdd);
  static unsigned int GetScore();
  static void ResetScore();
  static void SetNewHighScore(unsigned int pos, unsigned int score);

  void OnSDLUserEvent(const SDL_UserEvent& event) override;

  protected:
  ScoreManager();
  ~ScoreManager();
  CoffeeMaker::Coroutine LoadScores();
  CoffeeMaker::Coroutine SaveScores();

  private:
  static ScoreManager* _instance;
  static unsigned int _incrementAmount;

  unsigned int _score;
  HighScores _highScores;
  CoffeeMaker::File _scoreFile;
};

#endif
